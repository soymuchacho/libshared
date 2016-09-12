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
#include <Event.h>

namespace Shared
{

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
	void Engine_Loop();
	void ShutDown();
	bool GetSocket(int,basesocket_sptr &);
	bool GetSocket(unsigned long,unsigned long,basesocket_sptr &);
	bool Event_Add(EVENT * ev);
	bool Event_IO_Excute(EVENT_ID eid,int fd,int arg,void * args);
	bool Event_Del(EVENT * ev);
private:
	bool AddFd(int fd);
	bool RemoveFd(int fd);
	bool OnRecvSignal();
protected:
	int			m_EpollFd;
	int			m_FdNum;
};

}
#endif
