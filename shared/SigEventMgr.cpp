/**
 *	> Copyright(c) 2015 guqi
 *
 *	> LIBSHARED  VERSION :		0.0.1 
 *
 *	> File Name			 :		SigEventMgr.cpp
 *
 *	> Author			 :		guqi
 *
 *	> Mail				 :		guqi_282@126.com
 *
 *	> Created Time		 :		2015-10
 *
 * */

#include <network/SigEventMgr.h>
#include <network/SigEvent.h>
#include <network/MemoryPool.h>

namespace Shared
{

SigEventMgr::SigEventMgr()
{

}

SigEventMgr::~SigEventMgr()
{
	Clear();
}

void SigEventMgr::AddSigEvent(SigEvent * ev)
{
	if(ev == NULL)
	{
		return;
	}

	MutexLockGuard guard(&m_mutex);
	map<int,SigEvent *>::iterator itr;
	itr = m_sigmap.find(ev->sig);
	if(itr != m_sigmap.end())
	{
		SigEvent * oldev = itr->second;
		MM_DELETE(oldev);
	}
	m_sigmap[ev->sig] = ev;
}

SigEvent * SigEventMgr::GetSigEvent(int sig)
{
	MutexLockGuard guard(&m_mutex);
	map<int,SigEvent *>::iterator itr;
	itr = m_sigmap.find(sig);
	if(itr != m_sigmap.end())
	{
		return itr->second;
	}
	return NULL;
}

void SigEventMgr::RemoveSigEvent(int sig)
{
	MutexLockGuard guard(&m_mutex);
	map<int,SigEvent *>::iterator itr;
	itr = m_sigmap.find(sig);
	if(itr != m_sigmap.end())
	{
		SigEvent * ev = itr->second;
		MM_DELETE(ev);
		m_sigmap.erase(itr);
	}
}

void SigEventMgr::Clear()
{
	MutexLockGuard guard(&m_mutex);
	map<int,SigEvent *>::iterator itr;
	for(itr = m_sigmap.begin(); itr != m_sigmap.end(); itr++)
	{
		SigEvent * ev = itr->second;
		MM_DELETE(ev);
	}
	m_sigmap.clear();
}

void SigEventMgr::Execute(int sig)
{
	SigEvent * ev = GetSigEvent(sig);
	if(ev != NULL)
	{
		if(ev->handler != NULL)
		{
			ev->handler(ev->arg);
		}
//		RemoveSigEvent(sig);
	}
}

}

