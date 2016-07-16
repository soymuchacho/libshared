/**
 *	> Copyright(c) 2015 guqi
 *
 *	> LIBSHARED  VERSION :		0.0.1 
 *
 *	> File Name			 :		TimerEvent.h
 *
 *	> Author			 :		guqi
 *
 *	> Mail				 :		guqi_282@126.com
 *
 *	> Created Time		 :		2015-10
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

