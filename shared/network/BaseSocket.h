/**
 *	> Copyright(c) 2015 guqi
 *
 *	> LIBSHARED  VERSION :		0.0.1 
 *
 *	> File Name			 :		BaseSocket.h
 *
 *	> Author			 :		guqi
 *
 *	> Mail				 :		guqi_282@126.com
 *
 *	> Created Time		 :		2015-10
 *
 * */

#ifndef SHARED_BASESOCKET_H
#define SHARED_BASESOCKET_H	

#include <base/Log.h>
#include <network/MemoryPool.h>
#include <tr1/memory>

namespace Shared
{

class BaseSocket
{
public:
	BaseSocket() 
	{
		
	} 
	
	virtual ~BaseSocket() {	}
public:
	inline unsigned long GetFd()	{	return m_uFd;	}
	inline unsigned long GetCtime()	{	return m_ctime;	}

	inline void SetFd(int fd)	{	m_uFd = fd;	}
	inline void SetCtime(int ctime) {	m_ctime = ctime;	}
	inline bool IsConnected()	{	return m_connected;	}
	inline bool IsListen()	{	return m_bIsListen;	}
	inline void SetIp(char * ip)	{	strncpy(m_ip,ip,64);	}
	inline char * GetIp()	{	return m_ip;	}

	virtual void OnAccept(void * pointer) = 0;
	virtual void OnError() = 0; 
	virtual bool OnRead() = 0;
	virtual bool OnWrite() = 0;
	virtual bool OnRecvData() = 0;
	virtual int Write(void * ,int) = 0;
	virtual bool Writeable() = 0;
	
	virtual void Finalize() = 0;
	virtual void Connect() = 0;
	// disconnect the socket
	virtual void Disconnect() = 0;
	// delete the socket
	virtual void Delete() = 0;
	
	// write mutex.... can't write twice
	volatile long m_writeLock;
protected:
	unsigned long	m_uFd;
	unsigned long	m_ctime;
	char			m_ip[64];
	bool			m_connected;
	bool			m_bIsListen;		// is listen socket
};

typedef std::tr1::weak_ptr<BaseSocket> basesocket_wptr;
typedef std::tr1::shared_ptr<BaseSocket> basesocket_sptr;

}
#endif
