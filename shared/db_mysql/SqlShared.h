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
 * > File Name					:		SqlShared.h
 * > Author						:		soymuchacho
 * > Created Time				:		2017年01月06日 星期五 10时08分50秒
 * > brief						:		mysql数据库的应用动态连接库
 *
 * */

#ifndef SQL_SHARED_H
#define SQL_SHARED_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef OUT
#define OUT
#endif

#ifndef IN
#define IN
#endif

#ifndef SQLSHARED_API
#define SQLSHARED_API
#endif

typedef int         INT;
typedef bool        BOOL;
typedef void        VOID;
    

// 返回值定义
#define SQLSHARED_OK           0           /* 执行成功 */
#define SQLSHARED_ERROR       -1          /* 执行失败 */

/*
 *  @biref 查询语句的回调函数...
 */
typedef int (*selectcallback)(void * used,int argc, char ** argv,char ** coloumnname);

/*
 *  @brief 数据库连接句柄
 *  这是一个很有用的句柄，用于执行数据库操作，
 *  通过SqlShared_Open获得
 *
 */
typedef struct SqlHandle SqlHandle;

/*
 *  @brief 打开数据库，若数据库不存在，则创建此数据库！
 */
SQLSHARED_API INT SqlShared_Open(IN const char * host,IN const char * dbname,IN const char * username,IN const char * pwd,OUT SqlHandle ** ppDB);
// 执行sql语句.. 
SQLSHARED_API INT SqlShared_Exec(IN SqlHandle * pDB,selectcallback callback,IN void * used,OUT char * error);
// 关闭数据库
SQLSHARED_API INT SqlShared_Close(IN SqlHandle * pDB);

#ifdef __cplusplus
}
#endif

#endif


