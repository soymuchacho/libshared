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
 * > File Name					:		Epoll_Engine.cpp
 * > Author						:		soymuchacho
 * > Created Time				:		2015-10
 * > brief						:		epoll engine 
 *
 * */


#include <network/Epoll_Engine.h>
#include <Event.h>
#include <sys/epoll.h>
#include <base/Log.h>
#include <network/mm_ThreadPool.h>
#include <network/mm_Task.h>
#include <network/MemoryPool.h>
#include <network/Global_Val.h>
#include <base/TimeManager.h>

namespace Shared
{


//////////////////////////////////////////////////////////////////////////////
//					华丽的分割线		
////////////////////////////////////////////////////////////////////////////

Epoll_Engine::Epoll_Engine()
{

}

Epoll_Engine::~Epoll_Engine()
{
	ShutDown();
}

void Epoll_Engine::Initialize()
{


	// 初始化epoll
	m_EpollFd = epoll_create(MAX_DESCRIPTORS);
	ASSERT(m_EpollFd > 0);
	m_FdNum = 0;
	m_bRunning = true;
	// 初始化线程池
	bool ret = sMMThreads.InitThreadPool();
	ASSERT(ret != false);
}

bool Epoll_Engine::AddSocket(basesocket_sptr & socket)
{
	// 这里不需要加锁...
	// 因为每个连接的fd都是一一对应的，也就是唯一的。这里
	// 不存在同时操作一个fds[fd]，因此不需要加锁。
	if(!socket)
	{
		LOGDEBUG("debug","AddSocket socket is null");
		return false;
	}
	int fd = socket->GetFd();
	int use_count = fds[fd].use_count();
	//LOGDWORN("debug","fd %d use_count %d",fd,use_count);
	// 检测当前连接是否还在被占用，若被占用，将old connection 关闭
	if(use_count != 0)
	{
		//LOGDWORN("debug","base is not null! so disconnect,use_count %d",use_count);
		if(fds[fd]->GetFd() != 0)
			fds[fd]->Disconnect();
	}
	
	struct epoll_event ev;
	memset(&ev,0,sizeof(ev));
	ev.data.fd = fd;
	ev.events = (socket->Writeable()) ? EPOLLOUT : EPOLLIN;
	ev.events |= EPOLLET;
	ev.events |= EPOLLONESHOT;
	if(epoll_ctl(m_EpollFd,EPOLL_CTL_ADD,fd,&ev) == -1)
	{
		LOGDEBUG("debug","添加 fd %d 失败！error %d",fd,errno);
	}
	
	{
		MutexLockGuard lock(&m_mutex);
		fds[fd] = socket;
	}
	m_FdNum++;
	return true;
}

bool Epoll_Engine::AddFd(int fd)
{
	struct epoll_event ev;
	memset(&ev,0,sizeof(ev));
	ev.data.fd = fd;
	ev.events = EPOLLIN;
	ev.events |= EPOLLET;
	ev.events |= EPOLLONESHOT;
	if(epoll_ctl(m_EpollFd,EPOLL_CTL_ADD,fd,&ev) == -1)
	{
		LOGDEBUG("debug","添加 fd %d 失败！error %d",fd,errno);
	}
	return true;
}

bool Epoll_Engine::RemoveFd(int fd)
{
	struct epoll_event ev;
	memset(&ev,0,sizeof(ev));
	ev.data.fd = fd;
	ev.events = EPOLLIN;
	ev.events |= EPOLLET;
	ev.events |= EPOLLONESHOT;
	if(epoll_ctl(m_EpollFd,EPOLL_CTL_DEL,fd,&ev) == -1)
	{
		LOGDEBUG("debug","删除 fd %d 失败！error %d",fd,errno);
	}	
	return true;
}
void Epoll_Engine::DeleteSocket(basesocket_sptr & s)
{
	MutexLockGuard lock(&m_mutex);
	if(s)
	{
		fds[s->GetFd()].reset();
	}
	RemoveSocket(s);
}

void Epoll_Engine::WantRead(const basesocket_sptr & s)
{
	struct epoll_event ev;
	ev.data.fd = s->GetFd();
	ev.events = EPOLLIN | EPOLLET | EPOLLONESHOT;
	epoll_ctl(m_EpollFd,EPOLL_CTL_MOD,s->GetFd(),&ev);
}

bool Epoll_Engine::RemoveSocket(basesocket_sptr & socket)
{
	if(!socket)
		return false;
	int fd = socket->GetFd();

	struct epoll_event ev;
	memset(&ev,0,sizeof(ev));

	ev.data.fd = fd;
	ev.events = (socket->Writeable()) ? EPOLLOUT : EPOLLIN;
	ev.events |= EPOLLET;
	ev.events |= EPOLLONESHOT;
	epoll_ctl(m_EpollFd,EPOLL_CTL_DEL,fd,&ev);
	socket->SetFd(0);
	m_FdNum--;
	return true;
}

void Epoll_Engine::ShutDown()
{
	m_bRunning = false;
	for(int i = 0; i < MAX_DESCRIPTORS;i++)
	{
		if(fds[i])
		{
			fds[i]->Disconnect();
		}
	}
	RemoveFd(pipefd[0]);
	close(m_EpollFd);
}


void Epoll_Engine::Engine_Loop()
{
	const static int maxevents = 1024;
	struct epoll_event events[1024];
	
	if( socketpair(AF_UNIX,SOCK_STREAM,0,pipefd) == -1)
	{
		LOGDEBUG("debug","create pipe error!");
		return;
	}
	__shared_setnonblocking( pipefd[1] );
	AddFd(pipefd[0]);
	
	while(true)
	{
		time_t time_start = CURRENTTIME();
		time_t time_end = 0;
		
		int nfds = epoll_wait(m_EpollFd,events,maxevents,timeout);
		if(nfds <= 0)
		{
			// epoll_wait超时...执行时间心跳
			m_timeHeap->Tick();
			timeout = TIME_OUT;
		}
		else
		{
			time_end = CURRENTTIME();
			timeout = time_end - time_start;
			for(int i = 0; i < nfds; i++)
			{
				int fd = events[i].data.fd;
				/////////////////////////////////////////////////////
				//				信号处理
				////////////////////////////////////////////////////
				if(fd == pipefd[0] && events[i].events & EPOLLIN)
				{
					// 信号处理: 主循环来完成吧～～
					//LOGDEBUG("debug","收到信号～～");
					OnRecvSignal();
					continue;
				}
				////////////////////////////////////////////////////
				
				basesocket_sptr socket = fds[fd];

				if(!socket)
				{
					continue;
				}
				// 有一个潜在问题 ：当socket的异常时通过epoll_wait发现抛出，
				// EPOLLERR/EPOLLHUP事件，而不是read/write流程中发现，这时
				// 同样会误以为异常断开连接，所以只是再read/write流程中忽略
				// 相关错误码不够完善，当epoll_wait检测到socket错误时，仍然
				// 会当成fatal error处理。
				//
				// 正确的解决方法：
				// 1.read/write流程中对非知名错误（EINTR/EAGAIN/EWOULDBLOCK...）合理处理。
				// 2.遇到EPOLLERR/EPOLLHUP事件时，有两种做法：
				//		（1）不调用error异常流程，而是跟EPOLLIN一样调用读取流程，让读取流程
				//			 去确认/处理实际的错误.
				//		（2）通过getsocketopt SO_REEOR获取具体的错误码，并过滤掉非fatal错误.
				if(events[i].events & EPOLLHUP || events[i].events & EPOLLERR)
				{
					int eno = -1;
					int len = sizeof(int);
					if( getsockopt(fd,SOL_SOCKET,SO_ERROR,(void *)&eno,(socklen_t *)&len) == 0)
					{
						if(eno == 0 || eno == 32)
						{
							// 在OnWrite中已经做过处理，这里不必再处理！
							LOGDWORN("debug","do nothing");
							continue;
						}
						MM_Task * task = new (MM_MALLOC(sizeof(MM_Task))) MM_Task(SWITCH_MM_TASK_ONERROR,(Socket_Engine *)this,fd,socket->GetCtime());
						//MM_Task * task = new MM_Task(SWITCH_MM_TASK_ONERROR,(Socket_Engine *)this,fd,socket->GetCtime());
						if(task != NULL)
							sMMThreads.AddOneTask(task);
					}
				}
				else if(events[i].events & EPOLLIN) // recv data
				{
					MM_Task * task = new (MM_MALLOC(sizeof(MM_Task))) MM_Task(SWITCH_MM_TASK_ONREAD,(Socket_Engine *)this,fd,socket->GetCtime());
					//MM_Task * task = new  MM_Task(SWITCH_MM_TASK_ONREAD,(Socket_Engine *)this,fd,socket->GetCtime());
					if(task != NULL)
						sMMThreads.AddOneTask(task);
				}
				else if(events[i].events & EPOLLOUT) // send data
				{
					MM_Task * task = new (MM_MALLOC(sizeof(MM_Task))) MM_Task(SWITCH_MM_TASK_ONWRITE,(Socket_Engine *)this,fd,socket->GetCtime());
					//MM_Task * task = new  MM_Task(SWITCH_MM_TASK_ONWRITE,(Socket_Engine *)this,fd,socket->GetCtime());
					if(task != NULL)
						sMMThreads.AddOneTask(task);
				}
			}
		}
		sMMThreads.Run();
	}
}

void Epoll_Engine::WantWrite(const basesocket_sptr & s)
{
	if(s)
	{
		struct epoll_event ev;
		memset(&ev,0,sizeof(struct epoll_event));
		ev.data.fd = s->GetFd();
		ev.events = EPOLLOUT | EPOLLET | EPOLLONESHOT;

		epoll_ctl(m_EpollFd,EPOLL_CTL_MOD,s->GetFd(),&ev);
	}
}

bool Epoll_Engine::GetSocket(int index,basesocket_sptr & s)
{
	if(index >= 0)
	{
		MutexLockGuard lock(&m_mutex);
		s = fds[index];
		if(s)
		{
			return true;
		}
	}
	return false;
}

bool Epoll_Engine::GetSocket(unsigned long fd,unsigned long ctime,basesocket_sptr & s)
{
	MutexLockGuard lock(&m_mutex);
	if(fd >= 0)
	{
		//LOGDEBUG("debug","GetSocket fd %u,ctime %u",fd,ctime);
		if(fds[fd])
		{
			tr1::weak_ptr<BaseSocket> wptr(fds[fd]);
			s = wptr.lock();
			if(s)
			{
				if(s->GetCtime() == ctime)
				{
					return true;
				}
				else
					s.reset();
			}
		}
	}
	return false;
}

bool Epoll_Engine::OnRecvSignal()
{
	int sig;
	char signals[1024] = {0};
	bool ret = recv(pipefd[0],signals,sizeof(signals),0);
	
	if(ret == -1)
		return false;
	else if(ret == 0)
		return false;
	else
	{
		// 每个信号占一个字节～～
		for(int i = 0; i < ret; i++)
		{
			m_sigMgr->Execute((int)signals[i]);
		}
	}

	// EPOLLONESHUT 每次触发后，需要重新添加
	RemoveFd(pipefd[0]);
	AddFd(pipefd[0]);
	return true;
}

/*
 * @ brief 添加事件
 *
 * @ param 详见Event.h 中struct Event
 */ 

bool Epoll_Engine::Event_Add(EVENT * ev)
{
	if(ev == NULL)
	{
		LOGDWORN("debug","Event_Add : ev or basesocket is null");
		return false;
	}

	switch(ev->m_eType)
	{
		case EVENT_TYPE_TIMER:
			{
				// 添加时间事件				
				m_timeHeap->AddTimerEvent(ev);
			}
			break;
		case EVENT_TYPE_SIGNAL:
			{
				// 添加信号事件
				m_sigMgr->AddSigEvent(ev);
				// 注册信号
				__shared_register_signal(ev->m_eid);
			}
			break;
		case EVENT_TYPE_IO:
			{
				m_evMgr->Register_Event(ev);	
			}
			break;
		default:
			LOGDWORN("debug","none event type %d",ev->m_eType);
			return false;
	}
	return true;
}

bool Epoll_Engine::Event_IO_Excute(EVENT_ID eid,int fd,int arg,void * args)
{
	if(m_evMgr)
	{
		return m_evMgr->Event_Excute(eid,fd,arg,args);
	}
	return false;
}

bool Epoll_Engine::Event_Del(EVENT * ev)
{
	if(ev == NULL)
	{
		LOGDWORN("debug","Event_Del : ev or basesocket is null");
		return false;
	}

	switch(ev->m_eType)
	{
		case EVENT_TYPE_TIMER:
			{
				// 移除时间事件				
				m_timeHeap->DelTimerEvent(ev);
			}
			break;
		case EVENT_TYPE_SIGNAL:
			{
				// 移除信号事件
				m_sigMgr->RemoveSigEvent(ev->m_eid);
			}
			break;
		case EVENT_TYPE_IO:
			{
				// 移除IO事件
				m_evMgr->UnRegister_Event(ev->m_eid);	
				MM_DELETE(ev);
			}
			break;
		default:
			LOGDWORN("debug","none event type %d",ev->m_eType);
	}
}

}
