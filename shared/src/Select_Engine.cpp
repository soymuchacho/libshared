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
 * > File Name					:		Select_Engine.cpp
 * > Author						:		soymuchacho
 * > Created Time				:		2015-10
 * > brief						:		IO复用 select
 *
 * */


#include <network/Select_Engine.h>
#include <sys/socket.h>
#include <network/BaseSocket.h>
#include <common/Log.h>
#include <network/ThreadPool.h>
#include <network/Task.h>
#include <common/MemoryPool.h>
#include <network/Global_Val.h>
#include <utility/TimeManager.h>
#include <include/Event.h>

namespace Shared
{

Select_Engine::Select_Engine()
{
}

Select_Engine::~Select_Engine()
{

}

void Select_Engine::Initialize()
{
	// 初始化时间最小堆
	m_timeHeap = MM_NEW<MinHeap>();	
	ASSERT(m_timeHeap != NULL);
	
	// 初始化信号管理集合
	m_sigMgr = MM_NEW<SigEventMgr>();
	ASSERT(m_sigMgr != NULL);

	// 初始化Select
	FD_ZERO(&m_fdread);
	FD_ZERO(&m_fdwrite);
	FD_ZERO(&m_fdexception);
	
	m_FdNum = 0;
	m_bRunning = true;
	// 初始化线程池
	bool ret = sMMThreads.InitThreadPool();
	ASSERT(ret != false);
	
}

bool Select_Engine::AddSocket(basesocket_sptr & s)
{
	if(!s)
	{
		LOG2("L","TCP","socket fd is null!");
		return false;
	}

	int fd = s->GetFd();
	int use_count = fds[fd].use_count();
	if(use_count != 0)
	{
		if(fds[fd]->GetFd() != 0)
			fds[fd]->Disconnect();
	}

	// 加入监听集合
	FD_SET(fd,&m_fdread);
	
	MutexLockGuard lock(&m_mutex);
	fds[fd] = s;
	
	m_FdNum++;
	return true;
}

void Select_Engine::DeleteSocket(basesocket_sptr & s)
{
	MutexLockGuard lock(&m_mutex);
	if(!s)
	{
		return;
	}
	fds[s->GetFd()].reset();
	RemoveSocket(s);
}

bool Select_Engine::RemoveSocket(basesocket_sptr  & s)
{
	FD_CLR(s->GetFd(),&m_fdread);
	FD_CLR(s->GetFd(),&m_fdwrite);
	FD_CLR(s->GetFd(),&m_fdexception);
	m_FdNum--;
	return true;
}

bool Select_Engine::AddFd(int fd)
{
	FD_SET(fd,&m_fdread);
	FD_SET(fd,&m_fdwrite);
	FD_SET(fd,&m_fdexception);
	return true;
}

bool Select_Engine::RemoveFd(int fd)
{
	FD_CLR(fd,&m_fdread);
	FD_CLR(fd,&m_fdwrite);
	FD_CLR(fd,&m_fdexception);
	return true;
}

void Select_Engine::WantRead(const basesocket_sptr & s)
{

}

void Select_Engine::WantWrite(const basesocket_sptr & s)
{

}

void Select_Engine::ShutDown()
{
	m_bRunning = false;
	for(int i = 0; i < FD_SETSIZE; i++)
	{
		if(fds[i])	
		{
			fds[i]->Disconnect();
		}
	}
	RemoveFd(pipefd[0]);
}

void Select_Engine::Select_Loop()
{

	// 创建管道，监听信号事件
	if( socketpair(AF_UNIX,SOCK_STREAM,0,pipefd) == -1)
	{
		LOG2("L","TCP","socketpair error!");
		return ;
	}
	
	__shared_setnonblocking( pipefd[1] );
	AddFd(pipefd[0]);

	struct timeval time_start;
	time_start.tv_sec = 0;
	time_start.tv_usec = TIME_OUT;
	
	while(true)
	{
		// select 每次循环都要清空集合，否则不能检测描述符的变化
		ResetFd();
		// FD_SETSIZE 在select.h文件中，一般值为1024
		m_maxfd = FD_SETSIZE;
	
		int ret = 0;
		if(ret = select(m_maxfd,&m_fdread,&m_fdwrite,&m_fdexception,&time_start) < 0)
		{
			LOG2("L","SELECT","select error!");
			break;
		}

		if(ret < 0)
		{
			// select 超时返回
			m_timeHeap->Tick();
			time_start.tv_usec = TIME_OUT;
			continue;
		}
		// select 提前返回
		time_start.tv_usec = TIME_OUT - time_start.tv_usec;

		for(int i = 0; i < m_maxfd;i++)
		{
			int fd = i;
			basesocket_sptr socket = fds[fd];
			if(!socket)
				continue;

			if(FD_ISSET(i,&m_fdread))
			{
				// 可读
				if(fd == pipefd[0])
				{
					// 信号处理...	
					OnRecvSignal();
					continue;
				}
				else
				{
					MM_Task * task = new (MM_MALLOC(sizeof(MM_Task))) MM_Task(SWITCH_MM_TASK_ONREAD,(Socket_Engine *)this,fd,socket->GetCtime());
					if(task == NULL)
						LOG2("L","TCP","task malloc error!");
					else
						sMMThreads.AddOneTask(task);
				}
			}
			else if(FD_ISSET(i,&m_fdwrite))
			{
				// 可写
				MM_Task * task = new (MM_MALLOC(sizeof(MM_Task))) MM_Task(SWITCH_MM_TASK_ONWRITE,(Socket_Engine *)this,fd,socket->GetCtime());
				if(task == NULL)
					LOG2("L","TCP","task malloc error!");
				else
					sMMThreads.AddOneTask(task);
			}
			else if(FD_ISSET(i,&m_fdexception))
			{
				// 异常
				MM_Task * task = new (MM_MALLOC(sizeof(MM_Task))) MM_Task(SWITCH_MM_TASK_ONERROR,(Socket_Engine *)this,fd,socket->GetCtime());
				if(task == NULL)
					LOG2("L","TCP","task malloc error!");
				else
					sMMThreads.AddOneTask(task);
			}
		}
	}
}

bool Select_Engine::OnRecvSignal()
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
		// 每个信号占一个字节
		for(int i = 0; i < ret; i++)
		{
			m_sigMgr->Execute((int)signals[i]);
		}
	}
	return true;
}

void Select_Engine::ResetFd()
{
	FD_ZERO(&m_fdread);
	FD_ZERO(&m_fdwrite);
	FD_ZERO(&m_fdexception);
	
	
	for(int i = 0; i < FD_SETSIZE; i++)
	{
		if(fds[i])
		{
			// 该fd合法...
			FD_SET(i,&m_fdread);
			FD_SET(i,&m_fdwrite);
			FD_SET(i,&m_fdexception);
		}
	}
}

}
