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

namespace Shared
{

typedef void (*CallBackHandler)(void *);

enum Event_Type
{
	EVENT_TYPE_TIMER = 0,		/**< 时间事件 >*/
	EVENT_TYPE_SIGNAL,			/**< 信号事件 >*/
};

enum Event_Attr
{
	EVENT_ATTR_ONCE = 0,		/**< 事件只执行一次 >*/
	EVENT_ATTR_CYCLE,			/**< 事件总是执行,即永久事件 >*/
};

}// END NAMESPACE

#endif// END SHARED_EVENT_H
