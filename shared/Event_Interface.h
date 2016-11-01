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
 * > File Name					:		Event_Interface.cpp
 * > Author						:		soymuchacho
 * > Created Time				:		2015-10
 * > brief						:		事件接口 
 *
 * */

#ifndef SHARED_EVENT_INTERFACE_H
#define SHARED_EVENT_INTERFACE_H

#include <network/MemoryPool.h>
#include <network/Epoll_Engine.h>
#include <network/Min_Heap.h>
#include <network/BaseSocket.h>
#include <network/TcpSocket.h>
#include <network/ListenSocket.h>
#include <utility/TimeManager.h>
#include <base/Log.h>
#include <Event.h>
#include <network/Global_Val.h>
namespace Shared
{

/**< @brief 注册IO事件宏 >*/
#define shared_registerioevent(engine,evid,callback) \
	do{\
		Shared::RegisterEvent(engine,Shared::CreateEvent(evid, \
					Shared::EVENT_TYPE_IO,Shared::EVENT_ATTR_CYCLE, \
					callback)); \
	}while(0)

/**< @brief 注册时间永久事件宏，不用时需要手动删除事件 >*/
#define shared_registertimerevent(engine,ev,callback,fd,arg,args,interval) \
	do{\
		ev = Shared::CreateEvent(0,Shared::EVENT_TYPE_TIMER,Shared::EVENT_ATTR_CYCLE, \
				callback,fd,arg,args,interval); \
		Shared::RegisterEvent(engine,ev);\
	}while(0)

/**< @brief 注册单一时间事件（仅执行一次），不用时需要手动删除事件 >*/
#define shared_registertimersingleevent(engine,callback,fd,arg,args,interval) \
	do{\
		Shared::Event * ev = Shared::CreateEvent(0,Shared::EVENT_TYPE_TIMER,Shared::EVENT_ATTR_ONCE, \
				callback,fd,arg,args,interval); \
		Shared::RegisterEvent(engine,ev);\
	}while(0)

/**< @brief 注册信号事件 >*/
#define shared_registersignalevent(engine,ev,sig,callback,fd,arg,args) \
	do{ \
		ev = Shared::CreateEvent(sig,Shared::EVENT_TYPE_TIMER,Shared::EVENT_ATTR_CYCLE, \
				callback,fd,arg,args); \
		Shared::RegisterEvent(engine,ev);\
	}while(0)
/*
 *	@brief : 初始化消息分发器(套接字管理引擎类)
 *	
 *	@param : type	消息分发器类型
 */
template<class T>
static inline void Init_Engine(sockengine_sptr & sptr) 
{
	// 消息分发器分配空间
	T * ptr = MM_NEW<T>();

	// 消息分发器进行初始化
	if(ptr != NULL)
	{
		sptr.reset(ptr,SHARED_DELETE<T>());
		// 初始化全局消息分发器弱引用
		g_wpCurrentEngine = sptr;
		sptr->Initialize();
	}
}

/*
 *	@brief : 创建事件结构体,必须由RemoveEvent来销毁
 *
 *	@param : eid 事件id，由用户自己指定，若为sig事件，则为sig信号值，若为时间事件，则为0
 *	@param : type 事件类型，详见EVENT_TYPE 
 *	@param : attr 事件属性，详见EVENT_ATTR
 *	@param : callback 事件回调函数
 *	@param : fd IO事件时为socket文件描述符，信号事件为sig信号值，回调函数返回值之一
 *	@param : arg 回调函数返回值
 *	@param : args 回调函数返回值
 *	@param : interval 时间事件时，用于设置时间事件间隔时间，单位为毫秒
 */
static inline
Event * CreateEvent(EVENT_ID eid,EVENT_TYPE type,EVENT_ATTR attr,ev_callback callback,int fd = 0,int arg = 0,void * args = NULL,unsigned int interval = 0)
{

	Event * ev = MM_NEW<Event>();
	if(ev == NULL)
	{
		LOGDWORN("Worn","create Event error !");
		return NULL;
	}

	ev->m_eid = eid;
	ev->m_eType = type;
	ev->m_attr = attr;
	ev->m_alarm = CURRENTTIME() + interval;
	ev->m_interval = interval;
	ev->m_call = callback;
	ev->m_fd = fd;
	ev->m_arg = arg;
	ev->m_args = args;
	
	return ev;
}

/*
 *	@brief : 注册事件
 *	
 *	@param : bs 事件处理器 BaseSocket的智能指针
 *	@param : ev 事件
 */
static inline 
void RegisterEvent(sockengine_sptr se,Event *ev)
{
	if(se)
		se->Event_Add(ev);
}


/*
 *	@brief : 删除事件
 *
 *	@param : bs 事件处理器 BaseSocket的智能指针
 *	@param : ev 事件
 *
 */
static inline 
void RemoveEvent(sockengine_sptr se,Event * &ev) 
{ 
	if(se && ev != NULL)
	{
		se->Event_Del(ev);
		ev = NULL;
	}
}


/*
 *	@brief : 创建监听
 *
 *	@param : se 消息分发器引擎的智能指针
 *	@param : hostname ip地址
 *	@param : port 端口
 */
template <class T>
bool CreateListenSocket(sockengine_sptr se,char * hostname,u_short port)
{
	ListenSocket<T> * s = new  ListenSocket<T>();
	s->SetCtime(time(NULL));
	s->SetSocketEngine(se);
	if(s->Open(hostname,port) == false)
	{
		LOGDWORN("Worn","create listen ip%s , port%d error!",hostname,port);
		s->Disconnect();
		return false;
	}
	return true;
}

/*
 *	@biref : 连接socket
 *
 *	@param : sptr 消息分发器引擎的智能指针
 *	@param : hostname ip地址
 *	@param : port 端口
 */
template <class T>
bool ConnectTCPSocket(sockengine_sptr sptr,const char * hostname,u_short port,basesocket_sptr & bsptr)
{
	sockaddr_in conn;
	conn.sin_family = AF_INET;
	conn.sin_addr.s_addr = inet_addr(hostname);
	conn.sin_port = ntohs(port);

	int fd = socket(AF_INET,SOCK_STREAM,0);
	int result = connect(fd,(const sockaddr *)&conn,sizeof(sockaddr_in));
	if(result < 0)
	{
		LOGDWORN("Worn","connect ip%s , port%d error!",hostname,port);
		close(fd);
		return false;
	}

	T * s = MM_NEW<T>(fd,&conn);
	if(s == NULL)
	{
		LOGDWORN("Worn","Tcp malloc error !");
		close(fd);
		return false;
	}
	bsptr.reset(s,SHARED_DELETE<T>());

	s->SetSocketEngine(sptr);
	s->SetCtime(time(NULL));
	s->Finalize(bsptr);
	
	return true;
}

/*
 *  @brief : 回收消息分发器（套接字引擎类）
 *
 *	@param : sptr	引擎智能指针
 */

static inline 
void Shutdown_Engine(sockengine_sptr & sptr)
{
	if(sptr) 
	{ 
		sptr->ShutDown();  
		sptr.reset();
	}
}

} // END NAMESPACE SHARED

#endif// END SHARED_EVENT_INTERFACE_H
