/**
 *	> Copyright(c) 2015 guqi
 *
 *	> LIBSHARED  VERSION :		0.0.1 
 *
 *	> File Name			 :		TcpSocket.h
 *
 *	> Author			 :		guqi
 *
 *	> Mail				 :		guqi_282@126.com
 *
 *	> Created Time		 :		2015-10
 *
 * */

#ifndef SHARED_TCPSOCKET_H
#define SHARED_TCPSOCKET_H

#include <network/BaseSocket.h>
#include <include/Common.h>
#include <network/Buffer.h>
#include <base/Mutex.h>
#include <network/Socket_Engine.h>
#include <base/Log.h>

namespace Shared
{

#define MAX_RECVLENTH 2048


enum READ_STEP
{
	HEAD_STEP = 0,
	BODY_STEP = 1,
};

class TcpSocket : public BaseSocket
{
public:
	TcpSocket() {}
	TcpSocket(int fd,const struct sockaddr_in * peer);
	virtual ~TcpSocket();
public:
	Socket_Engine * GetSocketEngine(){	return se;	}
	void SetSocketEngine(Socket_Engine * _se) { se = _se;	}
	void SetPeer(const struct sockaddr_in * peer)	
	{
		if(peer == NULL) return;
		memcpy(&m_peer,peer,sizeof(struct sockaddr_in));
	}
public:
	virtual void OnAccept(void * pointer){}
	virtual void OnError();
	virtual bool OnRead();
	virtual bool OnWrite();
	bool OnRecvData() {}
	int Write(void *,int);	
	bool Writeable();

	virtual void Finalize();
	virtual void Connect(){}
	virtual void Disconnect();
	virtual void Delete();
public:
	virtual void OnConnect();
	virtual void OnDisConnect();
	void LockWriteBuffer()	{	m_writtenMutex.Lock();	}
	void UnLockWriteBuffer()	{	m_writtenMutex.UnLock();	}
protected:
	Buffer * readBuffer;
	Buffer * writeBuffer;

	Mutex m_writtenMutex;
	Mutex m_readMutex;
	sockaddr_in m_peer;
	Socket_Engine *se;
};

/*
 *	若连接类的对象非单实例，请使用该方法连接服务器
 *
 */
template <class T>
T * ConnectTCPSocket(Socket_Engine * se,const char * hostname,u_short port)
{
	sockaddr_in conn;
	conn.sin_family = AF_INET;
	conn.sin_addr.s_addr = inet_addr(hostname);
	conn.sin_port = ntohs(port);

	int fd = socket(AF_INET,SOCK_STREAM,0);
	int result = connect(fd,(const sockaddr *)&conn,sizeof(sockaddr_in));
	if(result < 0)
	{
		LOGDEBUG("debug","connect error!");
		close(fd);
		return 0;
	}

	T * s = new T(fd,&conn);
	s->SetSocketEngine(se);
	s->SetCtime(time(NULL));
	s->Finalize();
	return s;
}
/*
template<class D>
bool __ConnectTCPSocket(D * s,const char * hostname, u_short port)
{
	if(s == NULL)
		return false;
	sockaddr_in conn;
	conn.sin_family = AF_INET;
	conn.sin_addr.s_addr = inet_addr(hostname);
	conn.sin_port = ntohs(port);

	int fd = socket(AF_INET,SOCK_STREAM,0);
	int result = connect(fd,(const sockaddr *)&conn,sizeof(sockaddr_in));
	if(result < 0)
	{
		LOGDEBUG("debug","connect error!");
		close(fd);
		return false;
	}
	s->SetFd(fd);
	s->SetCtime(time(NULL));
	s->SetPeer(&conn);
	s->Finalize();
	return true;
}
*/
}
#endif
