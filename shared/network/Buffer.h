/**
 *	> Copyright(c) 2015 guqi
 *
 *	> LIBSHARED  VERSION :		0.0.1 
 *
 *	> File Name			 :		Buffer.h
 *
 *	> Author			 :		guqi
 *
 *	> Mail				 :		guqi_282@126.com
 *
 *	> Created Time		 :		2015-10
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
