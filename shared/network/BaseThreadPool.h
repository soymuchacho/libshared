/**
 *	> Copyright(c) 2015 guqi
 *
 *	> LIBSHARED  VERSION :		0.0.1 
 *
 *	> File Name			 :		BaseThreadPool.h
 *
 *	> Author			 :		guqi
 *
 *	> Mail				 :		guqi_282@126.com
 *
 *	> Created Time		 :		2015-10
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
