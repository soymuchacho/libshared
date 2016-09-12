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
 * > File Name					:		TimerEvent.h
 * > Author						:		soymuchacho
 * > Created Time				:		2015-10
 * > brief						:		 
 *
 * */

#ifndef SHARED_TIMER_EVENT_H
#define SHARED_TIMER_EVENT_H

#include <Event.h>

namespace Shared
{

class TimerEvent
{
public:
	TimerEvent()
		: handler(NULL),
		alarm_time(0),
		interval(0),
		ev_attr(EVENT_ATTR_ONCE),
		arg(NULL),
		min_heap_idx(-1)
	{
	}
	
	TimerEvent(Event_Attr attr)
		: handler(NULL),
		alarm_time(0),
		interval(0),
		ev_attr(attr),
		arg(NULL),
		min_heap_idx(-1)
	{
	}

	TimerEvent(const TimerEvent & event)
	{
		this->handler = event.handler;
		this->alarm_time = event.alarm_time;
		this->interval = event.interval;
		this->ev_attr = event.ev_attr;
		this->arg = event.arg;
		this->min_heap_idx = event.min_heap_idx;
	}
	const TimerEvent & operator=(const TimerEvent & event)
	{
		this->handler = event.handler;
		this->alarm_time = event.alarm_time;
		this->interval = event.interval;
		this->ev_attr = event.ev_attr;
		this->arg = event.arg;
		this->min_heap_idx = event.min_heap_idx;
		return *this;
	}
	~TimerEvent(){}
public:
	// 添加事件发生的时间 : 单位毫秒 CURRENTTIME() + interval
	unsigned int	alarm_time;
	// 与当前添加事件的时间的时间间隔 ： 单位毫秒
	unsigned int	interval;				
	// 回调函数
	void			(*handler)(void * arg);	// callback function
	// 回调函数参数,若为heap上的变量，用户需要自己释放
	void			* arg;
	// 定时事件属性
	Event_Attr		ev_attr;
	// min_heap 的结点信息
	int				min_heap_idx;
};

}

#endif

