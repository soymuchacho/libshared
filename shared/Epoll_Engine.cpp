/**
 *	> Copyright(c) 2015 guqi
 *
 *	> LIBSHARED  VERSION :		0.0.1 
 *
 *	> File Name			 :		Epoll_Engine.cpp
 *
 *	> Author			 :		guqi
 *
 *	> Mail				 :		guqi_282@126.com
 *
 *	> Created Time		 :		2015-10
 *
 * */


#include <network/Epoll_Engine.h>
#include <Event.h>
#include <sys/epoll.h>
#include <base/Log.h>
#include <network/mm_ThreadPool.h>
#include <network/mm_Task.h>
#include <network/MemoryPool.h>
#include <network/TimerEvent.h>
#include <network/Min_Heap.h>
#include <network/SigEvent.h>
#include <network/SigEventMgr.h>
#include <base/TimeManager.h>

namespace Shared
{

static const int	TIME_OUT = 60;
static int			pipefd[2];
static int			timeout = 60;

// 设置非阻塞
void __shared_setnonblocking(int fd)
{
	int old_option = fcntl(fd,F_GETFL);
	int new_option = old_option | O_NONBLOCK;
	fcntl(fd,F_GETFL,new_option);
}


// 信号处理函数
void __shared_signal_handler(int sig)
{
	//LOGDEBUG("debug","收到信号sig = %d",sig);
	int save_errno = errno;
	int msg = sig;
	if(send(pipefd[1],(char *)&msg,1,0) <= 0)
		LOGDEBUG("debug","send error!");
	errno = save_errno;
}

// 注册信号信号
void __shared_register_signal(int sig)
{
	struct sigaction sa;
	memset(&sa,'\0',sizeof(sa));
	sa.sa_handler = __shared_signal_handler;
	sa.sa_flags |= SA_RESTART;
	sigfillset( &sa.sa_mask );
	ASSERT( sigaction(sig,&sa,NULL) != -1);
}
//////////////////////////////////////////////////////////////////////////////
//					华丽的分割线		
////////////////////////////////////////////////////////////////////////////

Epoll_Engine::Epoll_Engine()
{

}

Epoll_Engine::~Epoll_Engine()
{
	MM_DELETE(m_timeHeap);
	MM_DELETE(m_sigMgr);
	ShutDown();
}

void Epoll_Engine::Initialize()
{

	printf("分配最小堆空间\n");
	m_timeHeap = MM_NEW<MinHeap>();
	ASSERT(m_timeHeap != NULL);
	printf("分配信号事件集合空间\n");
	m_sigMgr = MM_NEW<SigEventMgr>();
	ASSERT(m_sigMgr != NULL);
	m_EpollFd = epoll_create(MAX_DESCRIPTORS);
	ASSERT(m_EpollFd > 0);
	m_FdNum = 0;
	m_bRunning = true;
	bool ret = sMMThreads.InitThreadPool();
	ASSERT(ret != false);
}

bool Epoll_Engine::AddSocket(basesocket_sptr & socket)
{
	if(!socket)
	{
		LOGDEBUG("debug","AddSocket socket is null");
		return false;
	}
	int fd = socket->GetFd();
	int use_count = fds[fd].use_count();
	//LOGDWORN("debug","fd %d use_count %d",fd,use_count);
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


void Epoll_Engine::Epoll_Loop()
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
	RemoveFd(pipefd[0]);
	AddFd(pipefd[0]);
	return true;
}

/*
 *	@brief	添加时间事件
 */
void Epoll_Engine::AddTimerEvent(int ev_attr,int interval,void (*callback)(void *),void * arg)
{
	TimerEvent * ev = MM_NEW<TimerEvent>();
	if(ev == NULL)
	{
		LOGDWORN("debug","malloc error");
		return ;
	}
	ev->ev_attr = (Event_Attr)ev_attr;
	ev->alarm_time = CURRENTTIME() + interval;
	ev->interval = interval;
	ev->handler = callback;
	ev->arg = arg;
	m_timeHeap->AddTimerEvent(ev);
	return ;
}

/*
 *	@brief 添加信号事件
 *
 */
void Epoll_Engine::AddSigEvent(int ev_attr,int sig,void (*callback)(void *),void * arg)
{
	SigEvent * ev = MM_NEW<SigEvent>();
	if(ev == NULL)
	{
		LOGDWORN("debug","malloc error");
		return;
	}
	ev->sig_attr = (Event_Attr)ev_attr;
	ev->sig = sig;
	ev->handler = callback;
	ev->arg = arg;
	m_sigMgr->AddSigEvent(ev);
	__shared_register_signal(sig);
}

}
