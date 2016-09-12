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
	ListenSocket(){
		m_uFd = socket(AF_INET,SOCK_STREAM,0);

		u_long arg = 1;
		setsockopt(m_uFd,SOL_SOCKET,SO_REUSEADDR,(const char *)&arg,sizeof(u_long));

		m_writeLock = 0;
		m_connected = false;
		m_bIsListen = true;
	}

	virtual ~ListenSocket(){
	
	}

public:
	void OnAccept(void * pointer) {
	
	}
	
	void OnError() {
	
	}
	
	bool OnRead() {
		if(!m_connected) return true;
		socklen_t len = sizeof(sockaddr_in);
		new_fd = accept(m_uFd,(sockaddr *)&new_peer,&len);
		if(new_fd > 0)
		{
			T * s = MM_NEW<T>(new_fd,&new_peer);
			if(s == NULL)
			{
				LOGDWORN("Worn","accept new T error!");
				return true;
			}
			s->SetFd(new_fd);
			
			std::tr1::shared_ptr<Socket_Engine> eng_sptr;
			GetSocketEngine(eng_sptr);
			s->SetSocketEngine(eng_sptr);
			
			s->SetIp(inet_ntoa(new_peer.sin_addr));
			s->SetCtime(time(NULL));
			basesocket_sptr sptr(s,SHARED_DELETE<T>());
			s->Finalize(sptr);
		}
		return true;
	}
	
	bool OnWrite() {
	
	}
	
	bool OnRecvData() {
	
	}
	
	int Write(void *,int) {
	
	}
	
	void Finalize(basesocket_sptr s)	{
	
	}
	
	void Connect() {
	
	}
	
	void OnDisconnect() {
	
	}

	void Disconnect() {
		if(!m_connected)	return;
		m_connected = false;
		OnDisconnect();
		basesocket_sptr s;
		std::tr1::shared_ptr<Socket_Engine> eng_sptr;
		if(GetSocketEngine(eng_sptr))
		{
			if(eng_sptr->GetSocket(GetFd(),GetCtime(),s))
				eng_sptr->RemoveSocket(s);
		}
		close(m_uFd);
	}
	
	void Delete() {
		delete this;
	}
	
	bool Writeable() {	
		return false;	
	}

	bool Open(char * hostname,u_short port) {
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
		basesocket_sptr s = basesocket_sptr(this,SHARED_DELETE<BaseSocket>());
		std::tr1::shared_ptr<Socket_Engine> eng_sptr;
		if(GetSocketEngine(eng_sptr))
			eng_sptr->AddSocket(s);
		return true;
	}
protected:
	int			new_fd;				// 新接收的连接
	sockaddr_in new_peer;			// 新接收连接的节点
	sockaddr_in address;			// 当前监听的节点
};


}
#endif
