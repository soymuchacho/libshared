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
 * > File Name					:		Epoll_Engine.h
 * > Author						:		soymuchacho
 * > Created Time				:		2015-10
 * > brief						:		 
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
