/**
 *	> Copyright(c) 2015 guqi
 *
 *	> LIBSHARED  VERSION :		0.0.1 
 *
 *	> File Name			 :		BaseThread.h
 *
 *	> Author			 :		guqi
 *
 *	> Mail				 :		guqi_282@126.com
 *
 *	> Created Time		 :		2015-10
 *
 * */

#ifndef SHARED_BASETHREAD_H
#define SHARED_BASETHREAD_H

#include <pthread.h>
#include <base/Log.h>

namespace Shared
{
// 工作线程状态
enum WORK_THREAD_STATE
{
	WORK_THREAD_FREE = 0,		// 空闲状态	
	WORK_THREAD_SELECTED = 1,	// 线程选中
	WORK_THREAD_BUSY = 2,		// 繁忙状态
	WORK_THREAD_DEATH,			// 回收线程
};

class BaseThread
{
public:
	BaseThread()
	{
	
	}
	
	virtual ~BaseThread()	{ LOGDEBUG("debug","~BaseThread()");}
public:
	inline WORK_THREAD_STATE	GetState()		{	return m_state;	}
	inline void					SetState(WORK_THREAD_STATE state)	{	m_state = state;	}
	
	inline int					GetThreadID()	{	return m_ptid;	}
	inline void					SetThreadID(pthread_t ptid)	{	m_ptid = ptid;	}
protected:
	pthread_t			m_ptid;			// 线程标识符
	WORK_THREAD_STATE	m_state;		// 线程当前状态
};
}
#endif

