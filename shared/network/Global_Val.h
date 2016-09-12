/**
 *	> Copyright(c) 2015 guqi
 *
 *	> LIBSHARED  VERSION :		0.0.1 
 *
 *	> File Name			 :		Global_Val.h
 *
 *	> Author			 :		guqi
 *
 *	> Mail				 :		guqi_282@126.com
 *
 *	> Created Time		 :		2016-02
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
