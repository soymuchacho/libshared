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
 * > File Name					:		Event_Handles.cpp
 * > Author						:		soymuchacho
 * > Created Time				:		2015-10
 * > brief						:		事件操作
 *
 * */

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

	return Append(ev->m_eid,ev,true);
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
