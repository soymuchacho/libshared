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
 * > File Name					:		Thread.cpp
 * > Author						:		soymuchacho
 * > Created Time				:		2015-10
 * > brief						:		线程类 
 *
 * */

#include <network/Thread.h>
#include <network/BaseSocket.h>
#include <common/Log.h>
#include <network/Task.h>
#include <network/Socket_Engine.h>
#include <common/MemoryPool.h>

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
