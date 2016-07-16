/**
 *	> Copyright(c) 2015 guqi
 *
 *	> LIBSHARED  VERSION :		0.0.1 
 *
 *	> File Name			 :		mm_Thread.cpp
 *
 *	> Author			 :		guqi
 *
 *	> Mail				 :		guqi_282@126.com
 *
 *	> Created Time		 :		2015-10
 *
 * */

#include <network/mm_Thread.h>
#include <network/BaseSocket.h>
#include <base/Log.h>
#include <network/mm_Task.h>
#include <network/Socket_Engine.h>
#include <network/MemoryPool.h>

namespace Shared
{

MM_Thread::MM_Thread()
{
	m_task = NULL;
}

MM_Thread::~MM_Thread()
{
}

void * MM_Thread::Work(void * arg)
{
	// 自己回收自己,分离状态的线程,不能被其他线程回收和杀死
	pthread_detach(pthread_self());
	
	MM_Thread * thread = (MM_Thread *)arg;
	if(thread == NULL)
	{
		LOGDEBUG("debug","线程参数为NULL，线程退出");
		return NULL;
	}
	
	while(true)
	{
		WORK_THREAD_STATE state = thread->GetState();
		if(state == WORK_THREAD_BUSY)
		{
			// 执行！！！
			MM_Task * task = thread->GetTask();
			if(task != NULL)
			{
				basesocket_sptr sock;
				if(task->GetSocket(sock))
				{	
					switch(task->GetTaskSwitch())
					{
						case SWITCH_MM_TASK_ONERROR:
							sock->OnError();
							break;
						case SWITCH_MM_TASK_ONWRITE:
							{
								bool ret;
								ret = sock->OnWrite();
								if(ret == true)
								{
									Socket_Engine * se = task->GetSocketEngine();
									if(sock->Writeable() == false)
									{
										sock->m_writeLock = 0;
										se->WantRead(sock);
									}
									else
										se->WantWrite(sock);
								}
								else
								{
									sock->Disconnect();
								}
							}
							break;
						case SWITCH_MM_TASK_ONREAD:
							bool ret;
							ret = sock->OnRead();
							if(ret == true)
							{
								Socket_Engine * se = task->GetSocketEngine();
								if(sock->Writeable())
								{
									if(!sock->m_writeLock)
										++sock->m_writeLock;

									se->WantWrite(sock);
								}
								else
									se->WantRead(sock);
							}
							else
							{
								sock->Disconnect();
							}
							break;
					}
				}
				MM_DELETE(task);
			}
			thread->SetTask(NULL);
			thread->SetState(WORK_THREAD_FREE);
		}
		else if(state == WORK_THREAD_DEATH)
			break;
		usleep(1);
	}
	return NULL;
}

}
