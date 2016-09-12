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
 * > File Name					:		Common.h
 * > Author						:		soymuchacho
 * > Created Time				:		2015-10
 * > brief						:		 
 *
 * */

#ifndef SHARED_COMMON_H
#define SHARED_COMMON_H

/*
 *	@brief 通过某个结构中某个成员的指针，获得整个结构的指针
 *		  - 这个真心吊
 *	@param ptr		结构体中某个成员的指针
 *	@param type		结构体的类型
 *	@param member	第一个参数中的成员指针指向的成员在结构体中声明的成员名称
 * */

#define offsetof( TYPE,MEMBER ) ((size_t) &((TYPE *) 0)->MEMBER)

#ifdef WIN32
// WIN32下（不支持类型安全检查）
#define container_of( ptr, type, member) \
	((type *)(ptr)-offsetof(type,member))

#else
// LINUX下 (typeof 类型安全检测)
#define container_of( ptr, type, member) \
	({ /*const typeof((((type *)0)->member) * _mptr = (ptr));*/ (type *)((char *)ptr-offsetof(type,member)); })

#endif

#include "Typedef.h"

#include <ctime>
#include <cstdlib>
#include <cerrno>
#include <cassert>
#include <cstdarg>
#include <stdarg.h>

#define SAFE_DELETE(x) if((x) != NULL){ delete (x); (x) = NULL;}
#define WPAssert( assertion ) \
	{ if( !(assertion)) { fprintf(stderr,"\n%s:%i ASSERTION FAILED:\n %s\n",__FILE__,__LINE__,#assertion);assert(assertion);} }
#define ASSERT WPAssert

#include <cstdio>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <linux/limits.h>
#include <sys/wait.h>
#include <dirent.h>
#include <csignal>
#include <netdb.h>
#include <cstring>
#include <pthread.h>


#include <iostream>
#include <cctype>
using namespace std;

#include <vector>
#include <map>
#include <queue>


#endif

