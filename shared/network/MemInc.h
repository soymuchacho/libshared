/**
 *	> Copyright(c) 2015 guqi
 *
 *	> LIBSHARED  VERSION :		0.0.1 
 *
 *	> File Name			 :		MemInc.h
 *
 *	> Author			 :		guqi
 *
 *	> Mail				 :		guqi_282@126.com
 *
 *	> Created Time		 :		2015-10
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

