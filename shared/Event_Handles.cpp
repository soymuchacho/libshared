/*!
 *	\brief file 简易说明
 *
 *			Copyright(c) 2015 guqi。
 *
 *	\file		Event_Handles.cpp
 *
 *	\author		guqi_282@126.com
 *
 */
#include <network/Event_Handles.h>
#include <network/MemoryPool.h>

namespace Shared
{

EventHandles::EventHandles()
{

}

EventHandles::~EventHandles()
{

}

// 注册事件处理函数
bool EventHandles::Register_Event(EVENT * ev)
{
	if(ev == NULL)
		return false;

	return Append(ev->m_eid,ev);
}

bool EventHandles::Event_Excute(EVENT_ID eid, int fd , int arg , void * args)
{
	event_sptr ev;
	if(Get(eid,ev))
	{
		ev->m_call(fd,arg,args);
		return true;
	}
	return false;
}

// 获取事件处理函数
bool EventHandles::GetEvent(EVENT_ID eid,event_sptr& ev)
{
	return Get(eid,ev);
}

// 将事件处理函数删除
bool EventHandles::UnRegister_Event(EVENT_ID eid)
{
	return Remove(eid);
}

}
