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

class TcpSocket : public BaseSocket
{
public:
	TcpSocket() {}
	TcpSocket(int fd,const struct sockaddr_in * peer);
	virtual ~TcpSocket();
public:
	void SetPeer(const struct sockaddr_in * peer){
		if(peer == NULL) return;
		memcpy(&m_peer,peer,sizeof(struct sockaddr_in));
	}
public:
	int	 Write(void *,int);	
	bool Writeable();
	// 锁
	void LockWriteBuffer(){	
		m_writtenMutex.Lock();	
	}
	
	void UnLockWriteBuffer(){	
		m_writtenMutex.UnLock();	
	}
public:
	// 一般子类只需继承实现这3个函数
	// 数据已经存放在缓冲区中
	bool OnRecvData() {}
	// 多态
	virtual void OnConnect();
	virtual void OnDisConnect();
public:
	virtual void OnAccept(void * pointer){}
	virtual void OnError();
	virtual bool OnRead();
	virtual bool OnWrite();
	virtual void Finalize(basesocket_sptr s);
	virtual void Connect(){}
	virtual void Disconnect();
	virtual void Delete();
protected:
	sockaddr_in m_peer;							// 当前socket连接节点
	Mutex		m_readMutex;					// 读缓冲区线程锁
	Buffer		*readBuffer;					// 读缓冲区
	Mutex		m_writtenMutex;					// 写缓冲区线程锁
	Buffer		*writeBuffer;					// 写缓冲区
};


}
#endif
