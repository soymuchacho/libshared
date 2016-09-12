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
#include <Event.h>
#include <network/SigEventMgr.h>
#include <network/Min_Heap.h>
#include <network/MemoryPool.h>
#include <network/Event_Handles.h>


namespace Shared
{

#define MAX_DESCRIPTORS 65535

typedef std::tr1::shared_ptr<Shared::Socket_Engine> sockengine_sptr;
typedef std::tr1::weak_ptr<Shared::Socket_Engine> sockengine_wptr;


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
