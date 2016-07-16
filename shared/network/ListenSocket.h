/**
 *	> Copyright(c) 2015 guqi
 *
 *	> LIBSHARED  VERSION :		0.0.1 
 *
 *	> File Name			 :		ListenSocket.h
 *
 *	> Author			 :		guqi
 *
 *	> Mail				 :		guqi_282@126.com
 *
 *	> Created Time		 :		2015-10
 *
 * */

#ifndef SHARED_LISTENSOCKET_H
#define SHARED_LISTENSOCKET_H

#include <network/BaseSocket.h>
#include <include/Common.h>
#include <network/Socket_Engine.h>

namespace Shared
{

template <class T>
class ListenSocket : public BaseSocket
{
public:
	ListenSocket()
	{
		m_uFd = socket(AF_INET,SOCK_STREAM,0);

		u_long arg = 1;
		setsockopt(m_uFd,SOL_SOCKET,SO_REUSEADDR,(const char *)&arg,sizeof(u_long));

		m_writeLock = 0;
		m_connected = false;
		m_bIsListen = true;
	}
	virtual ~ListenSocket()
	{
	
	}
public:
	Socket_Engine * GetSocketEngine()	{	return se;	}
	void SetSocketEngine(Socket_Engine * _se) {	se = _se;	}
public:
	void OnAccept(void * pointer) {}
	void OnError() {}
	
	bool OnRead()
	{
		if(!m_connected) return true;
		socklen_t len = sizeof(sockaddr_in);
		new_fd = accept(m_uFd,(sockaddr *)&new_peer,&len);
		if(new_fd > 0)
		{
			T * s = new T(new_fd,&new_peer);
			if(s == NULL)
			{
				LOGDEBUG("debug","new T error!");
				return true;
			}
			s->SetFd(new_fd);
			s->SetSocketEngine(se);
			s->SetIp(inet_ntoa(new_peer.sin_addr));
			s->SetCtime(time(NULL));
			s->Finalize();
		}
		return true;
	}
	
	bool OnWrite()	{}
	
	bool OnRecvData()	{}
	
	int Write(void *,int) {}
	
	void Finalize()	{}
	void Connect()	{}
	
	void OnDisconnect()
	{
	
	}

	void Disconnect()
	{
		if(!m_connected)	return;
		m_connected = false;
		OnDisconnect();
		basesocket_sptr s;
		if(se->GetSocket(GetFd(),GetCtime(),s))
			se->RemoveSocket(s);
		close(m_uFd);
	}
	
	void Delete()
	{
		delete this;
	}
	
	bool Writeable() {	return false;	}
	bool Open(char * hostname,u_short port)
	{
		if(m_uFd < 0)
			return false;

		if(!strcmp(hostname,"0.0.0.0"))
			address.sin_addr.s_addr = htonl(INADDR_ANY);
		else
			address.sin_addr.s_addr = inet_addr(hostname);
		
		address.sin_family = AF_INET;
		address.sin_port = ntohs(port);
		if(bind(m_uFd,(const sockaddr *)&address,sizeof(sockaddr_in)) < 0)
		{
			LOG2("L","TCP","bind error!");
			return false;
		}
		if(listen(m_uFd,50) < 0)
		{
			LOG2("L","TCP","listen error!");
			return false;
		}
		m_connected = true;
		basesocket_sptr s = basesocket_sptr(this);
		se->AddSocket(s);
		return true;
	}
protected:
	int new_fd;
	sockaddr_in new_peer;
	sockaddr_in address;
	Socket_Engine * se;
};

template <class T>
bool CreateListenSocket(Socket_Engine * se,char * hostname,u_short port)
{
	ListenSocket<T> * s = new  ListenSocket<T>();
	s->SetCtime(time(NULL));
	s->SetSocketEngine(se);
	if(s->Open(hostname,port) == false)
	{
		s->Disconnect();
		return false;
	}
	return true;
}

}
#endif
