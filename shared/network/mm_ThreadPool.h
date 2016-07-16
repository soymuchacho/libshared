/**
 *	> Copyright(c) 2015 guqi
 *
 *	> LIBSHARED  VERSION :		0.0.1 
 *
 *	> File Name			 :		mm_ThreadPool.h
 *
 *	> Author			 :		guqi
 *
 *	> Mail				 :		guqi_282@126.com
 *
 *	> Created Time		 :		2015-10
 *
 * */

#ifndef SHARED_MM_THREADPOOL_H
#define SHARED_MM_THREADPOOL_H

#include <network/mm_Thread.h>
#include <base/Singleton.h>
#include <network/BaseThreadPool.h>
#include <base/Mutex.h>
#include <list>

namespace Shared
{

#define THREADS_NUM 10

class BaseTask;
class MM_Task;

class MM_ThreadPool : public BaseThreadPool , public Singleton< MM_ThreadPool >
{
	friend class Singleton< MM_ThreadPool >;
private:
	MM_ThreadPool();
	virtual ~MM_ThreadPool();
public:
	bool			InitThreadPool();
	BaseThread *	FetchOneThread();
	bool			AddOneTask(BaseTask * task);
	BaseTask *		FetchOneTask();
	void			Run();
protected:
	mutable Mutex m_mutex;
	MM_Thread  m_Threads[MAX_THREADS_NUM];
	list<BaseTask *> m_tasks;		// 任务队列！
};

#define sMMThreads (Shared::MM_ThreadPool::getSingleton())

}
#endif

