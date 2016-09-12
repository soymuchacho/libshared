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
 * > File Name					:		BaseThreadPool.h
 * > Author						:		soymuchacho
 * > Created Time				:		2015-10
 * > brief						:		线程池基类
 *
 * */

#ifndef SHARED_BASETHREADPOOL_H
#define SHARED_BASETHREADPOOL_H

#include <network/BaseThread.h>

namespace Shared
{

class BaseTask;
// 线程池支持的最大线程数量 ： 一般是 CPU数量 * 2
#define MAX_THREADS_NUM 24 

class BaseThreadPool
{
public:
	BaseThreadPool(int threadnum)
	{
		if(threadnum > MAX_THREADS_NUM || threadnum < 0)
		{
			m_tnum = MAX_THREADS_NUM;
		}
		else
			m_tnum = threadnum;
	}

	virtual ~BaseThreadPool()
	{
	
	}
public:
	inline int GetThreadNum()	{	return m_tnum;	}
public:
	// 初始化库
	virtual bool			InitThreadPool() = 0;
	// 选出一个空闲线程
	virtual BaseThread *	FetchOneThread() = 0;
	virtual bool			AddOneTask(BaseTask * task) = 0;
	virtual BaseTask *		FetchOneTask() = 0;
protected:
	int m_tnum;		// 当前池中最线程数量
};

}
#endif
