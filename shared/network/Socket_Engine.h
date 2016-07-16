/**
 *	> Copyright(c) 2015 guqi
 *
 *	> LIBSHARED  VERSION :		0.0.1 
 *
 *	> File Name			 :		Socket_Engine.h
 *
 *	> Author			 :		guqi
 *
 *	> Mail				 :		guqi_282@126.com
 *
 *	> Created Time		 :		2015-10
 *
 * */

#ifndef SHARED_SOCKET_ENGINE_H
#define SHARED_SOCKET_ENGINE_H

#include <network/BaseSocket.h>
#include <base/Mutex.h>

namespace Shared
{

#define MAX_DESCRIPTORS 65535

class Socket_Engine
{
public:
	Socket_Engine(){}
	virtual ~Socket_Engine(){}
public:
	virtual void Initialize() = 0;
	virtual bool AddSocket(basesocket_sptr &) = 0;
	virtual void DeleteSocket(basesocket_sptr &) = 0;
	virtual bool RemoveSocket(basesocket_sptr &) = 0;
	virtual void WantRead(const basesocket_sptr &) = 0;
	virtual void WantWrite(const basesocket_sptr &) = 0;
	virtual void ShutDown() = 0;
	virtual bool GetSocket(int,basesocket_sptr &) = 0;
	virtual bool GetSocket(unsigned long,unsigned long,basesocket_sptr &) = 0;
	virtual void AddTimerEvent(int ev_attr,int interval,void (*callback)(void *),void * arg) = 0;
	virtual void AddSigEvent(int ev_attr,int sig,void (*callback)(void *),void * arg) = 0;
protected:
	mutable Mutex		m_mutex;
	basesocket_sptr		fds[MAX_DESCRIPTORS];	
	bool				m_bRunning;
};
}
#endif
