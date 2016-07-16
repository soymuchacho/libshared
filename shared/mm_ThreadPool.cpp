/**
 *	> Copyright(c) 2015 guqi
 *
 *	> LIBSHARED  VERSION :		0.0.1 
 *
 *	> File Name			 :		mm_ThreadPool.cpp
 *
 *	> Author			 :		guqi
 *
 *	> Mail				 :		guqi_282@126.com
 *
 *	> Created Time		 :		2015-10
 *
 * */

#include <network/mm_ThreadPool.h>
#include <base/Log.h>
#include <network/mm_Task.h>

namespace Shared
{

// 在pthread主线程里屏蔽SIGPIPE异常函数
// 生成的子线程会继承父线程的屏蔽信号掩码
// 知识点详见：TcpSocket.cpp
static void ShieldPipeSignal()
{
	sigset_t signal_mask;
	sigemptyset(&signal_mask);
	sigaddset(&signal_mask,SIGPIPE);

	int rc = pthread_sigmask(SIG_BLOCK,&signal_mask,NULL);
	if(rc != 0)
	{
		LOGDEBUG("debug","block sigpipe error!");
	}
}

initializeSingleton( MM_ThreadPool );

MM_ThreadPool::MM_ThreadPool()
	:BaseThreadPool(THREADS_NUM)
{
	for(int i = 0; i < THREADS_NUM;i++)
	{
		m_Threads[i].SetState(WORK_THREAD_FREE);
	}
}

MM_ThreadPool::~MM_ThreadPool()
{
	for(int i = 0; i < m_tnum; i++)
	{
		m_Threads[i].SetState(WORK_THREAD_DEATH);
	}
}

bool MM_ThreadPool::InitThreadPool()
{
	ShieldPipeSignal();
	for(int i = 0; i < m_tnum;i++)
	{
		pthread_t ptid;
		if(pthread_create(&ptid,NULL,MM_Thread::Work,&m_Threads[i]) != 0)
		{
			LOGDEBUG("debug","创建线程失败！");
			return false;
		}
		m_Threads[i].SetThreadID(ptid);
	}
	return true;
}

BaseThread * MM_ThreadPool::FetchOneThread()
{
	BaseThread * thread = NULL;
	for(int i = 0; i < m_tnum;i++)
	{
		if(m_Threads[i].GetState() == WORK_THREAD_FREE)
		{
			thread = &m_Threads[i];
			// 设置线程为被选中状态
			thread->SetState(WORK_THREAD_SELECTED);
			break;
		}
	}
	return thread;
}

BaseTask * MM_ThreadPool::FetchOneTask()
{
	BaseTask * task = NULL;
	MutexLockGuard lock(&m_mutex);
	if(m_tasks.empty())
	{
		return NULL;
	}
	task = m_tasks.back();
	m_tasks.pop_back();
	return task;
}

bool MM_ThreadPool::AddOneTask(BaseTask * task)
{
	if(task == NULL)
		return false;
	MutexLockGuard lock(&m_mutex);
	m_tasks.push_front(task);
	return true;
}

void MM_ThreadPool::Run()
{
	MM_Task * task = NULL;
	MM_Thread * thread = NULL;
	while(true)
	{
		thread = (MM_Thread *)FetchOneThread();
		if(thread != NULL)
		{
			task = (MM_Task *)FetchOneTask();
			if(task != NULL)
			{
				thread->SetTask(task);
				thread->SetState(WORK_THREAD_BUSY);
			}
			else
			{
				thread->SetState(WORK_THREAD_FREE);
				break;
			}
		}
		else
		{
			break;
		}
	}
}

}
