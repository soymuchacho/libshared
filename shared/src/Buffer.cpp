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
 * > File Name					:		Buffer.cpp
 * > Author						:		soymuchacho
 * > Created Time				:		2015-10
 * > brief						:		缓冲区 
 *
 * */

#include <network/Buffer.h>
#include <common/Log.h>
#include <network/MemoryPool.h>

namespace Shared
{

Buffer::Buffer()
{
	pHead =  (BUFF_NODE *)MM_MALLOC(sizeof(BUFF_NODE));
	pHead->init();
	pEnd = pHead;
	curwptr = pHead;
	currptr = pHead;
	written = 0;
	crspace = 0;
	cwspace = BUFFER_NODE_SIZE;
	mNodenum = 1;
}

Buffer::~Buffer()
{
	destroy_all_data();	
}

void Buffer::IncrementWritten(int bytes)
{
	if(bytes > cwspace)
		bytes = cwspace;

	curwptr->crsize += bytes;
	curwptr->cwsize -= bytes;
	curwptr->wptr += bytes;
	
	written += bytes;
	cwspace -= bytes;
	crspace += bytes;
}

int Buffer::GetWriteSpace()
{
	int space = 0;
	if(curwptr == NULL)
	{
		malloc_buffer_node();
	}
	space += curwptr->cwsize;
	return space;
}

char * Buffer::GetWriteOffSet()
{
	if(curwptr == NULL)
	{
		malloc_buffer_node();
	}
	return curwptr->wptr;
}

char * Buffer::GetReadOffSet()
{
	if(currptr == NULL)
		return NULL;
	return currptr->rptr;
}

int Buffer::GetReadSpace()
{
	int space = 0;
	while(true)
	{
		if(currptr == NULL)
			break;
		space = currptr->crsize;
		if(space == 0)
		{
			if(currptr->cwsize == 0)
			{
				currptr = currptr->pnext;
				continue;
			}
			else
				break;
		}
		else
			break;
	}
	return space;
}

void Buffer::IncrementRead(int bytes)
{
	if(bytes <= 0)
		return;
	crspace -= bytes;
	currptr->crsize -= bytes;
	currptr->rptr += bytes;
}

unsigned long Buffer::GetReadSize()
{
	return crspace;
}

void Buffer::Write(char * data,int size)
{
	if(data == NULL)
		return;

	int leftsize = 0;
	while(true)
	{
		if(curwptr == NULL)
		{
			malloc_buffer_node();
		}

		if(curwptr->cwsize == 0)
		{
			malloc_buffer_node();
		}
		
		leftsize = curwptr->cwsize - size;
		
		
		if(leftsize >= 0)
		{
			memcpy(curwptr->wptr,data,size);
			curwptr->wptr += size;
			
			written += size;
			cwspace -= size;
			crspace += size;
			
			curwptr->cwsize -= size;
			curwptr->crsize += size;
			size = size - size;	
			
			break;
		}
		else
		{
			memcpy(curwptr->wptr,data,curwptr->cwsize);
			curwptr->wptr += curwptr->cwsize;
			curwptr->crsize += curwptr->cwsize;

			data += curwptr->cwsize;
			size -= curwptr->cwsize;

			written += curwptr->cwsize;
			cwspace -= curwptr->cwsize;
			crspace += curwptr->cwsize;
			
			curwptr->cwsize = 0;
		
			if(size <= 0)
				break;
		}
	}
}

int Buffer::Read(char * data,int size)
{
	if(data == NULL || crspace == 0)
	{
		return 0;
	}

	int readsize = 0;
	char * start = data;
	
	while(true)
	{
		if(currptr == NULL)
		{
			break;
		}
		
		int canReadsize = currptr->crsize;
		
		
		if(canReadsize == 0)
		{
			if(currptr->cwsize == 0)
			{
				currptr = currptr->pnext;
				continue;
			}
			else
			{
				break;
			}
		}
		
		if(canReadsize >= size)
		{
			memcpy(start,currptr->rptr,size);
			
			currptr->rptr += size;
			currptr->crsize -= size;
			crspace -= size;
			
			readsize += size;
			break;
		}
		else
		{
			memcpy(start,currptr->rptr,canReadsize);
			
			start += canReadsize;
			currptr->rptr += canReadsize;
			crspace -= canReadsize;

			readsize += canReadsize;	
			size -= canReadsize;
			
			currptr->crsize -= canReadsize;
			
			if(size <= 0)
				break;
		}
	}
	return readsize;
}

void Buffer::push_node(BUFF_NODE * node)
{
	pEnd->pnext = node;
	pEnd = node;
	curwptr = node;
	cwspace += BUFFER_NODE_SIZE;
	mNodenum++;
}

void Buffer::malloc_buffer_node()
{
	BUFF_NODE * node = (BUFF_NODE *)MM_MALLOC(sizeof(BUFF_NODE));
	node->init();
	push_node(node);
}

void Buffer::clear_all_data()
{
	BUFF_NODE * ptr = NULL;
	ptr = pHead->pnext;
	
	while(ptr != NULL)
	{
		BUFF_NODE * temp = ptr;
		ptr = ptr->pnext;

		temp->init();
		MM_FREE(temp);	
	}
	pHead->init();
	curwptr = pHead;
	currptr = pHead;
	written = 0;
	crspace = 0;
	cwspace = BUFFER_NODE_SIZE;
	mNodenum = 1;
	pEnd = pHead;
}

void Buffer::destroy_all_data()
{
	BUFF_NODE * ptr = NULL;
	ptr = pHead;
	
	while(ptr != NULL)
	{
		BUFF_NODE * temp = ptr;
		ptr = ptr->pnext;
		MM_FREE(temp);	
	}
}

}
