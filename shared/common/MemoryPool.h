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
 * > File Name					:		MemoryPool.h
 * > Author						:		soymuchacho
 * > Created Time				:		2015-10
 * > brief						:		 
 *
 * */


#ifndef SHARED_MEMORY_POOL_H
#define SHARED_MEMORY_POOL_H


/*
 *	@brief 内存池
 *	
 *	- 此类预先申请一块较大的内存，服务器中申请释放内存均
 *	  通过此类
 *
 *	- 内存池的优点：可控性，提高效率，避免系统内存碎片等等，
 *	  总之就是好,尼玛，好苍白。
 *  
 *  - 在不改动原有代码的情况下，接替new 和 delete ,malloc 和 free(目前没实现)
 *    能够展示内存数据使用的情况（便于查找内存泄露）
 *    快速实现内存回收和再利用
 *    支持多线程内存申请
 * 
 *	- 版本1 ：固定内存池，即内存池由一系列大小的内存块组成，每一个
 *	  内存块又包含了固定数量和大小的内存单元。内存单元用数组保存
 *
 *	  版本2 ： 内存池由一系列大小相同的内存块组成，每一个内存块可分为若干
 *	  大小的内存单元，内存单元动态划分，初始化完成后，只有一个内存单元，每
 *	  申请一次，分出一个内存单元，释放时，和前后两个空闲内存单元合并成一个
 *	  内存单元。内存单元用双链表保存。
 *
 *	  目前采用版本2
 *
 *	- 内存池初始化后，只向系统申请一个内存块，随后会根据需要动态向系统
 *	  申请更多的内存块。
 *  
 *  - 申请内存的前两个字节，用来存放申请信息。所以实际申请大小为用户size + 4
 * 
 * */
//////////////////////////////////////////////////////////////
#include <common/MemInc.h>
#include <common/Mutex.h>
#include <common/Singleton.h>
#include <common/Log.h>
#include <typeinfo>

namespace Shared
{

// 单键
class MemoryPool : public Singleton< MemoryPool >
{
	friend class Singleton < MemoryPool >; 
private:
	MemoryPool();
	~MemoryPool();
public:
	// 申请一段内存
	// size 申请内存的大小

	void * Malloc(size_t size);
	// 释放一段内存
	// 释放内存的头指针
	void Free(void * ptr);

	bool DisplayPool();

private:
	void InitMemBlock(MemBlock * block,size_t size);	// 初始化一个内存块	
	MemBlock * IncreaseMemBlock();				// 增加一个内存块
	
	/*
	 *	@brief 从内存块中查找合适的内存单元，并从内存单元中划分内存，并返回，用于版本2
	 *
	 */
	void * CheckAndSet(MemBlock * pBlock,size_t size);
	/*
	 *	@brief 内存单元中划分内存,哦嗯与版本2
	 */
	void * DivisionUnit(MemBlock * pBlock,MemUnit * pUnit,size_t size);
	/* 
	 * @brief	打印内存块
	 * @retval	true	验证成功
	 * @retval	false	要打印的内存非法
	 * */
	bool DisplayMemBlock(MemBlock * pBlock);
	void DestoryPool();						// 销毁内存池
	// 检测内存泄露
	bool CheckMemoryLeak();
protected:
	MemBlock *	m_Block;				// 块链表头
	uint32		m_BlockNum;				// 块数量
	Mutex		m_mutex;				// 信号量，多线程有用
};

static inline MemoryPool & Shared_MemPool()
{
	return MemoryPool::getSingleton();
}

static void * MM_MALLOC(unsigned int size)
{
	return MemoryPool::getSingleton().Malloc(size);
}

// placement new


// 只使用于不带参数的构造函数的类
template<class T>
static T * MM_NEW()
{
	unsigned int size = sizeof(T);
	void * mem = MemoryPool::getSingleton().Malloc(size);
	T * ptr = new (mem) T();
	return ptr;
}

// 用于BaseSocket类的构造
template<class T>
static T * MM_NEW(unsigned int fd,unsigned int ctime)
{

	unsigned int size = sizeof(T);
	void * mem = MemoryPool::getSingleton().Malloc(size);
	T * ptr = new (mem) T(fd,ctime);
	return ptr;
}

// 用于BaseSocket类的构造
template<class T>
static T * MM_NEW(int fd,const struct sockaddr_in * peer)
{

	unsigned int size = sizeof(T);
	void * mem = MemoryPool::getSingleton().Malloc(size);
	T * ptr = new (mem) T(fd,peer);
	return ptr;
}

// 可变参数
template<class T,class...ARGS>
static T * MM_NEW(ARGS...args)
{
	unsigned int size = sizeof(T);
	void * mem = MemoryPool::getSingleton().Malloc(size);
	T * ptr = new (mem) T(args...);
	return ptr;
}

/*
template<class T,class T0,class T1,class T2>
static T * MM_NEW(T0 a0, T1 a1, T2 a2)
{
	unsigned int size = sizeof(T);
	void * mem = MemoryPool::getSingleton().Malloc(size);
	T * ptr = new (mem) T(a0,a1,a2);
	return ptr;
}
*/
// 用于与new相对应的delete
template<class T>
static void MM_DELETE(T *& ptr)
{
	if(ptr != NULL)
	{
		(ptr)->~T();
		MemoryPool::getSingleton().Free(ptr);
		ptr = NULL;
	}
}

// 用于智能指针释放
template<class T>
struct SHARED_DELETE
{
	void operator () (T * ptr)
	{
		if(ptr != NULL)
		{
			LOGDEBUG("debug"," %s shared delete",typeid(ptr).name());
			(ptr)->~T();
			MemoryPool::getSingleton().Free(ptr);
			ptr = NULL;
		}
	}
};

template<class T>
static void MM_FREE(T *& ptr)
{
	if(ptr != NULL)
	{
		MemoryPool::getSingleton().Free(ptr);
		ptr = NULL;
	}
}

}

/*
#define sMemPool Shared::MemoryPool::getSingleton()

#define MALLOC( size ) Shared::MemoryPool::getSingleton().Malloc((size))

#define FREE( ptr ) \
	if((ptr) != NULL) \
	{ \
		Shared::MemoryPool::getSingleton().Free((ptr)); \
		(ptr) = NULL; \
	} 

// placement new
#define MM_NEW(type) \
	new ( MALLOC( ( sizeof( type ) ) ) )  

#define MM_NEW2(type) Shared::mm_new<type>()

#define MM_DELETE(type,ptr)	 \
	if( (ptr) != NULL) \
	{ \
		(ptr)->~type(); \
		FREE( (ptr) ); \
	} 

#define MM_DELETE2(ptr) Shared::mm_del(&ptr) 
*/

#endif

