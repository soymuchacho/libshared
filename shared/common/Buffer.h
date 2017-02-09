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
 * > File Name					:		Buffer.h
 * > Author						:		soymuchacho
 * > Created Time				:		2015-10
 * > brief						:		 
 *
 * */

#ifndef SHAERD_BUFFER_H
#define SHARED_BUFFER_H

#include <include/Common.h>

namespace Shared
{
/*
 *
 * @brief 缓冲区
 *
 */

#define BUFFER_NODE_SIZE 4096				// 缓冲区大小
#define BUFFER_NODE_INIT_NUM 2

// 缓冲区链表节点
typedef struct buff_node
{
	char * wptr;		// where to write
	char * rptr;		// where to read
	char * bptr;		// buffer where begin
	char * eptr;			// where end
		
	int crsize;			// can read size
	int cwsize;			// can write size
	
	char node[BUFFER_NODE_SIZE];
	struct buff_node * pnext;

	void init()
	{
		crsize = 0;
		cwsize = BUFFER_NODE_SIZE;

		memset(node,0,BUFFER_NODE_SIZE);
		wptr = node;
		rptr = node;
		bptr = node;
		eptr = node + BUFFER_NODE_SIZE - 1;
		pnext = NULL;
	}
}BUFF_NODE;

class Buffer
{
public:
	Buffer();
	~Buffer();
public:
	void IncrementWritten(int bytes);
	void IncrementRead(int bytes);
	int GetReadSpace();
	int GetWriteSpace();
	char * GetWriteOffSet();
	char * GetReadOffSet();
	unsigned long GetReadSize();
	void Write(char * data,int size);
	int Read(char * data,int size);
public:
	void push_node(BUFF_NODE * node);
	void malloc_buffer_node();
	void clear_all_data();
	void destroy_all_data();
protected:
	unsigned long written;		// has been written size
	unsigned long cwspace;		// left can be written size
	unsigned long crspace;		// can be read size
	
	BUFF_NODE * pHead;
	BUFF_NODE * pEnd;
	BUFF_NODE * curwptr;	// cureent write buffer_node
	BUFF_NODE * currptr;	// cureent read buffer_node

	int mNodenum;
};
}
#endif
