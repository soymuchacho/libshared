/*
 * Copyright (c) 2012-2016 soymuchacho <guqi_282@126.com>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * > LIBSHARED  VERSION 		:		0.0.1 
 * > File Name					:		MemoryPool.cpp
 * > Author						:		soymuchacho
 * > Created Time				:		2015-10
 * > brief						:		内存池 
 *
 * */

#include <network/MemoryPool.h>
#include <Event_Interface.h>
#include <base/Log.h>

namespace Shared
{

initializeSingleton( MemoryPool );

MemoryPool::MemoryPool()
{
	//LOGDEBUG("debug","内存块申请了 %u 内存",MEMORY_BLOCK_SIZE);
	m_Block = (MemBlock *)malloc(MEMORY_BLOCK_SIZE);
	ASSERT(m_Block != NULL);
	InitMemBlock(m_Block,MEMORY_BLOCK_SIZE);
	m_Block->pNext = NULL;
	m_BlockNum = 1;
}

MemoryPool::~MemoryPool()
{
	DestoryPool();
}
int i = 0;

void * MemoryPool::Malloc(size_t size)
{
	MutexLockGuard lock(&m_mutex);
	//void * ptr = (void *)malloc(size);
	//return ptr;
	// 实际分配大小，需要加上内存单元头
	unsigned int acsize = size + sizeof(MemUnit);
	
	if(size > MEMORY_BLOCK_SIZE - sizeof(MemBlock) - sizeof(MemUnit) + 1 )
	{
		LOG2("L","MEMORY","malloc size too big !");
		return NULL;
	}

	void * pMemory = NULL;

	MemBlock * pBlock = m_Block;

	while(pBlock != NULL)
	{
		// 内存块中查找
		if(pBlock->u_size >= acsize)
		{
			// 该内存块空闲大小大于要分配的内存大小
			// 到该内存块中进行分配
			pMemory = CheckAndSet(pBlock,acsize);

			if(pMemory != NULL)
			{
				return pMemory;
			}
		}
		pBlock = pBlock->pNext;
	}

	// 没有找到合适的内存，再分配内存块
	MemBlock * newBlock = IncreaseMemBlock();
	if(newBlock != NULL)
	{
		pMemory = CheckAndSet(newBlock,acsize); 	
	}	
	return pMemory;
}

void MemoryPool::Free(void * ptr)
{
	MutexLockGuard lock(&m_mutex);
	//if(ptr != NULL)
	//	free(ptr);
	//return;
	// 找到对应的内存单元头
	MemUnit * pUnit = (MemUnit *)((char *)ptr - sizeof(MemUnit));
	void * pMemory = (void *)(pUnit->u_addr);

	//printf("pMemory(%p),%x,ptr(%p),要是放的大小(%u)\n",pMemory,pUnit->u_addr,ptr,pUnit->u_size);
	if(pMemory != ptr)
	{
		// 是否要引发异常退出?
		//printf("内存释放失败！pMemory(%p),%x,ptr(%p)\n",pMemory,pUnit->u_addr,ptr);
	//	LOGDEBUG("debug","释放出错！内存单元(%d):模块地址(0x%p) 首地址（0x%x）,大小（%u）,是否被占用（%d）pNext(%p)",1,
	//			pUnit,pUnit->u_addr,pUnit->u_size,pUnit->isBusy,pUnit->pNext);
		ASSERT(pMemory == ptr);
		return ;
	}

	if(pUnit->isBusy == false)
	{
		LOGDEBUG("debug","释放出错，该内存单元未被分配！内存单元(%d):模块地址(0x%p) 首地址（0x%x）,大小（%u）,是否被占用（%d）pNext(%p)",1,
				pUnit,pUnit->u_addr,pUnit->u_size,pUnit->isBusy,pUnit->pNext);
	//	ASSERT(pUnit->isBusy == true);
		return;
	}

	pUnit->isBusy = false;
	
	// 找到模块头,并修改模块头的数据
	MemBlock * pBlock = NULL;
	MemUnit * pHead = pUnit;
	MemUnit * pTmp = NULL; 
	for( ; ; )
	{
		pTmp = pHead;
		if(pTmp != NULL)
		{
			pHead = pTmp->pPrior;
			if(pHead == NULL)
			{
				pHead = pTmp;
				break;
			}
		}
	}
	pBlock = (MemBlock *)((char *)pHead - sizeof(MemBlock));

	// 先找到后一个内存单元，尝试合并
	MemUnit * nextUnit = pUnit->pNext;
	if(nextUnit != NULL)
	{
		// 若后一个为空闲块则合并
		if(nextUnit->isBusy == false)
		{
			pUnit->pNext = nextUnit->pNext;
			if(nextUnit->pNext != NULL)
				nextUnit->pNext->pPrior = pUnit;
			
			pBlock->u_size += pUnit->u_size + sizeof(MemUnit);
			pBlock->u_count--;
			pUnit->u_size = pUnit->u_size + nextUnit->u_size + sizeof(MemUnit);
		}
	}

	// 再找到前一个内存单元尝试合并
	MemUnit * priorUnit = pUnit->pPrior;	
	if(priorUnit != NULL)
	{
		if(priorUnit->isBusy == false)
		{
			//LOGDEBUG("debug","要释放单元的大小%u",pUnit->u_size);
			priorUnit->pNext = pUnit->pNext;
			if(pUnit->pNext != NULL)
				pUnit->pNext->pPrior = priorUnit;
			priorUnit->u_size = priorUnit->u_size + pUnit->u_size + sizeof(MemUnit);
			//LOGDEBUG("debug","与前一单元合并,合并后大小%u",priorUnit->u_size);
			pBlock->u_size += pUnit->u_size + sizeof(MemUnit);
			pBlock->u_count--;
		}
	}
}

// 从内存单元中划分内存，进行分配
void * MemoryPool::DivisionUnit(MemBlock * pBlock,MemUnit * pUnit,size_t size)
{
	// size 包括用户要分配的内存以及内存单元头sizeof(MemUnit)大小
	if(pUnit->u_size < size)
		return NULL;
	// 原内存单元
	void * pMemory = (void *)((char *)pUnit + sizeof(MemUnit));
	MemUnit * pUnit2 = NULL;	
	// 内存单元大小大于要分配的大小才进行分割，否则不分割
	unsigned int nsize = size - sizeof(MemUnit);
	unsigned int leftsize = pUnit->u_size - nsize;

	if(leftsize > sizeof(MemUnit))
	{
		// 新划分内存单元
		void * pMemory_2 = (void *)((char *)pUnit + size + sizeof(MemUnit));
		MemUnit * pUnit_2 = (MemUnit *)((char *)pUnit + size);

		pUnit_2->u_addr =(uint64)((char *)pMemory_2);
		pUnit_2->u_size = pUnit->u_size - size;
		pUnit_2->isBusy = false;
		pUnit_2->pPrior = pUnit;
		pUnit_2->pNext = pUnit->pNext;
		
		if(pUnit->pNext != NULL)
			pUnit->pNext->pPrior = pUnit_2;
		
		pUnit->pNext = pUnit_2;
		// 只有大于的时候需要设置，其他情况不需要改变
		pUnit->u_size = nsize;//pUnit->u_size - pUnit_2->u_size - sizeof(MemUnit);
		pBlock->u_count++;

		pUnit2 = pUnit_2;
	}
	else if(leftsize < 0)
		return NULL;
	pBlock->u_size = pBlock->u_size - pUnit->u_size - sizeof(MemUnit);
	pUnit->isBusy = true;
	return pMemory;
}

void * MemoryPool::CheckAndSet(MemBlock * pBlock,size_t size)
{
	// 查看内存块中的内存单元
	void * pMemory = NULL;
	MemUnit * pUnit = pBlock->pbUnit;
	while(pUnit != NULL)
	{
		// 该单元是否空闲
		if(pUnit->isBusy == false)
		{
			// 检测内存单元可分配大小是否大于等于要分配的内存大小
			if(pUnit->u_size >= size)
			{
				// 找到合适的内存单元，将内存单元划分	
				pMemory = DivisionUnit(pBlock,pUnit,size);
				if(pMemory != NULL)
				{
					//LOGDEBUG("debug","-------内存块信息--------");
					//LOGDEBUG("debug","内存单元数量：%d",pBlock->u_count);
					//LOGDEBUG("debug","空闲空间大小：%d",pBlock->u_size);
					break;
				}
			}
		}
		pUnit = pUnit->pNext;		
	}
	return pMemory;
}

void MemoryPool::InitMemBlock(MemBlock * block,size_t size)
{
	// 初始化时，内存单元仅有一个
	MemUnit * pUnit = (MemUnit *)block->data;
	pUnit->u_addr = (uint64)(block->data + sizeof(MemUnit));
	pUnit->u_size = MEMORY_BLOCK_SIZE - sizeof(MemBlock) - sizeof(MemUnit) + 1;
	pUnit->isBusy = false;
	pUnit->pPrior = NULL;
	pUnit->pNext = NULL;

	block->u_count = 1;
	block->u_size = pUnit->u_size;
	block->pbUnit = pUnit;
}

MemBlock * MemoryPool::IncreaseMemBlock()
{

	MemBlock * block = NULL;
	
	block = (MemBlock *)malloc(MEMORY_BLOCK_SIZE);
	if(block == NULL)
		return NULL;
	InitMemBlock(block,MEMORY_BLOCK_SIZE);
	
	block->pNext = m_Block;
	m_Block = block;
	m_BlockNum++;
	return block;
}

void MemoryPool::DestoryPool()
{
	MemBlock * pNode = m_Block; 
	while(pNode != NULL)
	{
		MemBlock * pTmp = pNode;
		pNode = pTmp->pNext;
		free(pTmp);
		pTmp = NULL;
	}
	m_Block = NULL;
}

bool MemoryPool::DisplayPool()
{
	MemBlock * pBlock = m_Block;
	int i = 0;
	while(pBlock != NULL)
	{
		i++;
		LOGDEBUG("debug","############ 内存块%d ############\n",i);
		MemUnit * pUnit = pBlock->pbUnit;
		int i = 0;
		while(pUnit != NULL)
		{
			LOGDEBUG("debug","内存单元(%d : %p):首地址（0x%x）,大小（%u）,是否被占用（%d）,pPrior(%p),pNext(%p)\n",i,pUnit,
					pUnit->u_addr,pUnit->u_size,pUnit->isBusy,pUnit->pPrior,pUnit->pNext);
			pUnit = pUnit->pNext;
			i++;
		}
		pBlock = pBlock->pNext;
	}
	return true;
}

bool MemoryPool::DisplayMemBlock(MemBlock * pBlock)
{
	if(pBlock == NULL)
		return false;
	
	MemUnit * pUnit = pBlock->pbUnit;
	int i = 0;

	while(pUnit != NULL)
	{
		LOGDEBUG("debug","内存单元(%d):首地址（0x%x）,大小（%u）,是否被占用（%d）pNext(%p)",i,
						pUnit->u_addr,pUnit->u_size,pUnit->isBusy,pUnit->pNext);
		
		pUnit = pUnit->pNext;
		i++;
	}
	return true;
}

bool MemoryPool::CheckMemoryLeak()
{
	MemBlock * pBlock = m_Block;
	int i = 0;
	while(pBlock != NULL)
	{
		i++;
		MemUnit * pUnit = pBlock->pbUnit;
		int j = 0;
		while(pUnit != NULL)
		{
			j++;
			MemUnit * pUnitNext = pUnit->pNext;
			if(pUnitNext != NULL)
			{
				if(pUnit->u_addr + pUnit->u_size + sizeof(MemUnit) != pUnitNext->u_addr )
				{
					LOGDEBUG("debug","！！！！！！！！！！！！！！！！！ 内存块泄露！！！！！！！！！！！！！！！");
					LOGDEBUG("debug","内存单元(%d):模块地址(0x%p) 首地址（0x%x）,大小（%u）,是否被占用（%d）pNext(%p)",j,
							pUnit,pUnit->u_addr,pUnit->u_size,pUnit->isBusy,pUnit->pNext);
					
					LOGDEBUG("debug","内存单元(%d):模块地址(0x%p) 首地址（0x%x）,大小（%u）,是否被占用（%d）pNext(%p)",j+1,
							pUnitNext,pUnitNext->u_addr,pUnitNext->u_size,pUnitNext->isBusy,pUnitNext->pNext);
					return false;
				}

			}
			pUnit = pUnit->pNext;
		}
		pBlock = pBlock->pNext;
	}
	return true;
}

}
