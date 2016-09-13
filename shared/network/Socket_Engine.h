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
 * > File Name					:		Socket_Engine.h
 * > Author						:		soymuchacho
 * > Created Time				:		2015-10
 * > brief						:		Locker 
 *
 * */


#ifndef SHARED_SOCKET_ENGINE_H
#define SHARED_SOCKET_ENGINE_H

#include <network/BaseSocket.h>
#include <base/Mutex.h>
#include <Event.h>
#include <network/SigEventMgr.h>
#include <network/Min_Heap.h>
#include <network/MemoryPool.h>
#include <network/Event_Handles.h>


namespace Shared
{

typedef std::tr1::shared_ptr<Shared::Socket_Engine> sockengine_sptr;
typedef std::tr1::weak_ptr<Shared::Socket_Engine> sockengine_wptr;
#define MAX_DESCRIPTORS 65535

class Socket_Engine
{
public:
	Socket_Engine()
	{
		// 初始化最小堆,即时间事件管理集合
		m_timeHeap = MM_NEW<MinHeap>();
		ASSERT(m_timeHeap != NULL);
		// 初始化信号管理集合
		m_sigMgr = MM_NEW<SigEventMgr>();
		ASSERT(m_sigMgr != NULL);
		// 初始化IO事件管理结合
		m_evMgr = MM_NEW<EventHandles>();
		ASSERT(m_evMgr != NULL);
	}
	
	virtual ~Socket_Engine()
	{
		MM_DELETE(m_timeHeap);
		MM_DELETE(m_sigMgr);
		MM_DELETE(m_evMgr);
	}
public:
	virtual void Initialize() = 0;
	virtual bool AddSocket(basesocket_sptr &) = 0;
	virtual void DeleteSocket(basesocket_sptr &) = 0;
	virtual bool RemoveSocket(basesocket_sptr &) = 0;
	virtual void WantRead(const basesocket_sptr &) = 0;
	virtual void WantWrite(const basesocket_sptr &) = 0;
	virtual void Engine_Loop() = 0;
	virtual void ShutDown() = 0;
	virtual bool GetSocket(int,basesocket_sptr &) = 0;
	virtual bool GetSocket(unsigned long,unsigned long,basesocket_sptr &) = 0;
	virtual bool Event_Add(Event * ev) = 0;
	virtual bool Event_IO_Excute(EVENT_ID eid,int fd,int arg,void * args) = 0;
	virtual bool Event_Del(Event * ev) = 0;
protected:
	bool				m_bRunning;					// 状态
	mutable Mutex		m_mutex;					// 线程锁
	basesocket_sptr		fds[MAX_DESCRIPTORS];		// 描述符管理集合
protected:
	MinHeap				* m_timeHeap;				// 时间事件管理集合：最小堆
	SigEventMgr			* m_sigMgr;					// 信号事件管理集合
	EventHandles		* m_evMgr;					// IO事件管理集合
};
}
#endif
