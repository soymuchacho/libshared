/**
 *	> Copyright(c) 2015 guqi
 *
 *	> LIBSHARED  VERSION :		0.0.1 
 *
 *	> File Name			 :		Event.h
 *
 *	> Author			 :		guqi
 *
 *	> Mail				 :		guqi_282@126.com
 *
 *	> Created Time		 :		2015-10
 *
 * */

#ifndef SHARED_EVENT_H
#define SHARED_EVENT_H

#include <functional>
#include <base/NonCopyable.h>
#include <tr1/memory>

namespace Shared
{

typedef unsigned int EVENT_ID;
typedef void * (*EV_CALLBACK)(int fd, int arg, void * args);
typedef std::function<void*(int,int,void *)> ev_callback;

// 事件类型
typedef enum Event_Type
{
	EVENT_TYPE_TIMER = 0,		/**< 时间事件 >*/
	EVENT_TYPE_SIGNAL,			/**< 信号事件 >*/
	EVENT_TYPE_IO,				/**< IO事件 >*/
}EVENT_TYPE;

// 事件属性
typedef enum Event_Attr
{
	EVENT_ATTR_ONCE = 0,		/**< 事件只执行一次 >*/
	EVENT_ATTR_CYCLE,			/**< 事件总是执行,即永久事件 >*/
}EVENT_ATTR;

// 事件
typedef struct Event
{
	EVENT_ID		m_eid;			/**< 事件id >*/
	EVENT_TYPE		m_eType;		/**< 事件类型 >*/
	EVENT_ATTR		m_attr;			/**< 事件属性 >*/
	unsigned int	m_alarm;		/**< 时间事件第一次触发的时间:当前时间 + 间隔时间 >*/
	unsigned int	m_interval;		/**< 时间事件触发时间间隔,循环事件要用到 >*/
	ev_callback		m_call;			/**< 事件回调函数 >*/
	int				m_fd;			/**< 触发此事件的socket文件描述符，信号和时间事件设为0 >*/
	int				m_arg;			/**< 回调函数的参数 >*/
	void *			m_args;			/**< 回调函数的参数 >*/
}EVENT;

typedef std::tr1::shared_ptr<Event>	event_sptr;
typedef	std::tr1::weak_ptr<Event>	event_wptr;

}// END NAMESPACE

#endif// END SHARED_EVENT_H
