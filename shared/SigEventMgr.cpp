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
#include <network/MemoryPool.h>
#include <utility/ObjectMgr.hpp>

namespace Shared
{

SigEventMgr::SigEventMgr()
{

}

SigEventMgr::~SigEventMgr()
{
	Clear();
}

bool SigEventMgr::AddSigEvent(Event * ev)
{
	if(!ev)
		return false;

	return Append(ev->m_eid,ev);
}

bool SigEventMgr::GetSigEvent(int sig,event_sptr& ev)
{
	return Get(sig,ev);
}

bool SigEventMgr::RemoveSigEvent(int sig)
{
	return Remove(sig);
}

void SigEventMgr::Clear()
{
	Clear();
}

void SigEventMgr::Execute(int sig)
{
	event_sptr ev;
	if(GetSigEvent(sig,ev))
	{
		if(ev->m_call)
		{
			ev->m_call(ev->m_fd,ev->m_arg,ev->m_args);
		}
	}
}

}

