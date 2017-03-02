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
 * > File Name					:		MemInc.h
 * > Author						:		soymuchacho
 * > Created Time				:		2015-10
 * > brief						:		 
 *
 * */

#ifndef SHARED_MEMORY_INCLUDE_H
#define SHARED_MEMORY_INCLUDE_H

#include <include/Typedef.h>

namespace Shared
{
#define MEMORY_BLOCK_SIZE (1024 * 1024 * 100)			// 100M内存 

#pragma pack(1)

// 内存单元,最小内存分配单元,在每个内存单元头sizeof(MemUnit)个字节存放 
typedef struct _MemUnit
{
	uint64 u_addr;			// 内存单元首地址 : 不包括单元头
	uint32 u_size;			// 内存单元大小,不包括单元头
	bool   isBusy;			// 是否被占用
	struct _MemUnit * pPrior;	// 前一个
	struct _MemUnit * pNext;	// 后一个
}MemUnit;

// 内存块
typedef struct _MemBlock
{
	uint32		u_count;			// 当前内存单元的总数量
	uint32		u_size;				// 空闲空间大小
	MemUnit *	pbUnit;				// 内存单元双向链表头
	struct _MemBlock * pNext;		// 下一个内存块
	char		data[1];
}MemBlock;

#pragma pack()

}
#endif

