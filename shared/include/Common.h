/**
 *	> Copyright(c) 2015 guqi
 *
 *	> LIBSHARED  VERSION :		0.0.1 
 *
 *	> File Name			 :		Common.h
 *
 *	> Author			 :		guqi
 *
 *	> Mail				 :		guqi_282@126.com
 *
 *	> Created Time		 :		2015-10
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

