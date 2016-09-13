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
 * > File Name					:		BaseSocket.h
 * > Author						:		soymuchacho
 * > Created Time				:		2015-10
 * > brief						:		封装socket基类 
 *
 * */

#ifndef SHARED_BASESOCKET_H
#define SHARED_BASESOCKET_H	

#include <base/Log.h>
#include <network/MemoryPool.h>
#include <tr1/memory>

namespace Shared
{

class Socket_Engine;
class BaseSocket;
// 智能指针定义
typedef std::tr1::weak_ptr<Shared::BaseSocket> basesocket_wptr;
typedef std::tr1::weak_ptr<Shared::BaseSocket> BaseSocket_wptr;
typedef std::tr1::shared_ptr<Shared::BaseSocket> basesocket_sptr;
typedef std::tr1::shared_ptr<Shared::BaseSocket> BaseSocket_sptr;


// 操作...

class BaseSocket
{
public:
	BaseSocket() 
	{
		
	} 
	
	virtual ~BaseSocket() {	}
public:
	inline unsigned long GetFd() {	
		return m_uFd;	
	}
	inline unsigned long GetCtime()	{
		return m_ctime;	
	}
	inline void SetFd(int fd) {	
		m_uFd = fd;	
	}
	inline void SetCtime(int ctime) {	
		m_ctime = ctime;	
	}
	inline bool IsConnected() {	
		return m_connected;	
	}
	inline bool IsListen() {	
		return m_bIsListen;	
	}
	inline void SetIp(char * ip) {	
		strncpy(m_ip,ip,64);	
	}
	inline char * GetIp() {	
		return m_ip;	
	}
	inline void SetSocketEngine(std::tr1::shared_ptr<Socket_Engine> & sptr){
		m_wpEngine = sptr;
	}
	inline bool GetSocketEngine(std::tr1::shared_ptr<Socket_Engine>& sptr){
		sptr = m_wpEngine.lock();
		if(sptr)
			return true;
		return false;
	}
public:
	// 接受连接
	virtual void OnAccept(void * pointer) = 0;
	// 连接出错
	virtual void OnError() = 0; 
	// 读取数据
	virtual bool OnRead() = 0;
	// 发送数据
	virtual bool OnWrite() = 0;
	// 开始接收数据
	virtual bool OnRecvData() = 0;
	// 数据解析
	virtual bool Dispatch() = 0;
	// 发送
	virtual int Write(void * ,int) = 0;
	// 是否可写
	virtual bool Writeable() = 0;
	// 接收连接结束时
	virtual void Finalize(basesocket_sptr s) = 0;
	// 连接连上时
	virtual void Connect() = 0;
	// disconnect the socket
	virtual void Disconnect() = 0;
	// delete the socket
	virtual void Delete() = 0;
public:
	// write mutex.... can't write twice
	volatile long m_writeLock;
protected:
	std::tr1::weak_ptr<Socket_Engine>	m_wpEngine;			// 事件分发器的智能指针
	unsigned long						m_uFd;				// 连接描述符
	unsigned long						m_ctime;			// 连接时间
	char								m_ip[64];			// ip地址
	bool								m_connected;		// 是否连接
	bool								m_bIsListen;		// is listen socket
};


}
#endif
