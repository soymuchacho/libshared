/**
 *	> Copyright(c) 2015 guqi
 *
 *	> LIBSHARED  VERSION :		0.0.1 
 *
 *	> File Name			 :		mm_Thread.h
 *
 *	> Author			 :		guqi
 *
 *	> Mail				 :		guqi_282@126.com
 *
 *	> Created Time		 :		2015-10
 *
 * */


#ifndef SHARED_MM_THREAD_H
#define SHARED_MM_THREAD_H

#include <network/BaseThread.h>

namespace Shared
{

class MM_Task;

class MM_Thread : public BaseThread
{
public:
	MM_Thread();
	virtual ~MM_Thread();
public:
	static void * Work(void * arg);
public:
	void SetTask(MM_Task * task)	{	m_task = task;	}
	MM_Task * GetTask()		{	return m_task;		}
protected:
	// 要执行的任务
	MM_Task * m_task;
};

}
#endif
