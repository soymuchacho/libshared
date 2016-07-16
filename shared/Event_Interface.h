/**
 *	> Copyright(c) 2015 guqi
 *
 *	> LIBSHARED  VERSION :		0.0.1 
 *
 *	> File Name			 :		Event_Interface.h
 *
 *	> Author			 :		guqi
 *
 *	> Mail				 :		guqi_282@126.com
 *
 *	> Created Time		 :		2015-10
 *
 * */

#ifndef SHARED_EVENT_INTERFACE_H
#define SHARED_EVENT_INTERFACE_H

#include <network/MemoryPool.h>
#include <network/Epoll_Engine.h>
#include <network/Min_Heap.h>
#include <Event.h>

namespace Shared
{
/*
 *	@brief : 初始化消息分发器(套接字引擎类)
 *	
 *	@param : type	消息分发器类型
 */
template<class T>
static inline T * Init_Engine() 
{
	T * ptr = MM_NEW<T>();
	if(ptr != NULL)
		ptr->Initialize();
	return ptr;
}
	
/*
 *	@brief : 向消息分发器中注册定时事件
 *	EVENT_ATTR_ONCE = 0,		**< 事件只执行一次 >*
 *	EVENT_ATTR_CYCLE,			**< 事件总是执行,即永久事件 >*
 */

static inline void RegisterTimerEvent(Socket_Engine * engine,Event_Attr ev_attr,uint32 interval,CallBackHandler callback,void * arg)
{ 
	if( engine != NULL)
	{ 
		engine->AddTimerEvent(ev_attr,interval,callback,arg);
	} 
}

/*
 *	@brief : 向消息分发器中注册信号事件
 */
static inline void RegisterSigEvent(Socket_Engine * engine,Event_Attr ev_attr,uint32 sig,CallBackHandler callback,void * arg) 
{ 
		if( engine != NULL) 
		{ 
			engine->AddSigEvent(ev_attr,sig,callback,arg); 
		} 
}
/*
 *	@brief : 向消息分发器中注册事件
 *
 *	@param : engine		消息分发器类型
 *			 ev_type	事件类型 （时间？信号？）
 *			 ev_attr	事件属性 （一次？多次？）
 *			 interval	若为定时事件，此为时间间隔(单位毫秒)，否则填0
 *			 sig		若为信号时间，此为信号，否则填0
 *			 callback	事件的回调函数
 *			 arg		回调函数参数
 */
static inline void RegisterEvent(Socket_Engine * engine,Event_Type ev_type,Event_Attr ev_attr,uint32 interval,uint32 sig,CallBackHandler callback,void * arg) 
{ 
	if( ev_type == Shared::EVENT_TYPE_TIMER) 
	{ 
		RegisterTimerEvent(engine,ev_attr,interval,callback,arg); 
	} 
	else if( ev_type == Shared::EVENT_TYPE_SIGNAL) 
	{ 
		RegisterSigEvent(engine,ev_attr,sig,callback,arg); 
	} 
}
/*
 *  @brief : 回收消息分发器（套接字引擎类）
 *
 *	@param : type	消息分发器（套接字引擎类）类型，如Epoll_Engine
 *	@param : engine	引擎指针
 */
static void Delete_Engine(Socket_Engine * engine) 
{ 
	if(engine != NULL)
	{
		engine->ShutDown(); 
		MM_DELETE(engine); 
	}
}

} // END NAMESPACE SHARED

#endif// END SHARED_EVENT_INTERFACE_H
