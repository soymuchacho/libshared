/*!
 *	\brief file 简易说明
 *
 *			Copyright(c) 2015 guqi。
 *
 *	\file		Event_Handles.h
 *
 *	\author		guqi_282@126.com
 *
 */
#ifndef SHARED_EVENT_HANDLES_H
#define SHARED_EVENT_HANDLES_H

#include <Event.h>
#include <base/NonCopyable.h>
#include <utility/ObjectMgr.hpp>

namespace Shared
{

// 存放IO事件
class EventHandles : public Utility::ObjectMgr< EVENT_ID,EVENT >,public noncopyable
{
public:
	EventHandles();
	~EventHandles();
public:
	// 注册事件处理函数
	bool Register_Event(EVENT * ev);
	// 执行事件处理函数
	bool Event_Excute(EVENT_ID eid, int fd , int arg , void * args);
	// 获取事件处理函数
	bool GetEvent(EVENT_ID eid,event_sptr& ev);
	// 将事件处理函数删除
	bool UnRegister_Event(EVENT_ID eid);
};

}// END namespace Shared

#endif
