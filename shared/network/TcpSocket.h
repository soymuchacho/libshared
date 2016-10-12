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
 * > File Name					:		TcpSocket.h
 * > Author						:		soymuchacho
 * > Created Time				:		2015-10
 * > brief						:		
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
	virtual void LoadHandles() {}
	// 数据已经存放在缓冲区中
	virtual bool OnRecvData();
	// 从缓冲区中读取数据
	virtual bool Dispatch() {}
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
