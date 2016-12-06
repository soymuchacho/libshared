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
 * > File Name					:		Global_Val.h
 * > Author						:		soymuchacho
 * > Created Time				:		2015-10
 * > brief						:		
 *
 * */

#ifndef SHARED_GLOBAL_VAL_H
#define SHARED_GLOBAL_VAL_H

#include <network/Socket_Engine.h>

namespace Shared
{

/** < 此文件存放libshared所需的所有全局变量及函数 >*/

///////////////////////////////////////////////////
//					全局变量					//
//////////////////////////////////////////////////

	
/* 当前所使用的事件多路分发器实例*/
static std::tr1::weak_ptr<Shared::Socket_Engine> g_wpCurrentEngine;

#define GLOBAL_CURRENT_ENGINE Shared::g_wpCurrentEngine

/* 计时最小单位（60毫秒）*/
static const int	TIME_OUT = 60;

/* 用于设置多路分发器超时时间变量，当多路分发器未超时返回时，
 * 需要重新计算剩余时间，并设置下一次多路分发器的超时时间
 * */
static int			timeout = 60;

/* 管道，用于监听信号 */
static int			pipefd[2];



//////////////////////////////////////////////////////
/*					全局函数						*/
//////////////////////////////////////////////////////



// 将套接字设置成非阻塞
static void __shared_setnonblocking(int fd)
{
	int old_option = fcntl(fd,F_GETFL);
	int new_option = old_option | O_NONBLOCK;
	fcntl(fd,F_SETFL,new_option);
}


// 信号处理函数
static void __shared_signal_handler(int sig)
{
	//LOGDEBUG("debug","收到信号sig = %d",sig);
	int save_errno = errno;
	int msg = sig;
	if(send(pipefd[1],(char *)&msg,1,0) <= 0)
		LOGDEBUG("debug","send error!");
	errno = save_errno;
}

// 注册信号信号
static void __shared_register_signal(int sig)
{
	struct sigaction sa;
	memset(&sa,'\0',sizeof(sa));
	sa.sa_handler = __shared_signal_handler;
	sa.sa_flags |= SA_RESTART;
	sigfillset( &sa.sa_mask );
	ASSERT( sigaction(sig,&sa,NULL) != -1);
}

}	// END SHARED
#endif // END SHARED_GLOBAL_VAL_H
