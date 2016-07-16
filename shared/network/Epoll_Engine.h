/**
 *	> Copyright(c) 2015 guqi
 *
 *	> LIBSHARED  VERSION :		0.0.1 
 *
 *	> File Name			 :		Epoll_Engine.h
 *
 *	> Author			 :		guqi
 *
 *	> Mail				 :		guqi_282@126.com
 *
 *	> Created Time		 :		2015-10
 *
 * */

#ifndef SHARED_EPOLL_ENGINE_H
#define SHARED_EPOLL_ENGINE_H

#include <network/Socket_Engine.h>
#include <network/BaseSocket.h>
#include <base/Mutex.h>

namespace Shared
{

class MinHeap;
class SigEventMgr;

class Epoll_Engine : public Socket_Engine
{
public:
	Epoll_Engine();
	virtual ~Epoll_Engine();
public:
	void Initialize();
	bool AddSocket(basesocket_sptr &);
	void DeleteSocket(basesocket_sptr &);
	bool RemoveSocket(basesocket_sptr &);
	void WantRead(const basesocket_sptr &);
	void WantWrite(const basesocket_sptr &);
	void ShutDown();
	bool GetSocket(int,basesocket_sptr &);
	bool GetSocket(unsigned long,unsigned long,basesocket_sptr &);
	void AddTimerEvent(int ev_attr,int interval,void (*callback)(void *),void * arg);
	void AddSigEvent(int ev_attr,int sig,void (*callback)(void *),void * arg);
public:
	void Epoll_Loop();
private:
	bool AddFd(int fd);
	bool RemoveFd(int fd);
	bool OnRecvSignal();
protected:
	MinHeap		* m_timeHeap;
	SigEventMgr * m_sigMgr;
	int			m_EpollFd;
	int			m_FdNum;
};

}
#endif
