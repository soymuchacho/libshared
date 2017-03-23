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
 * > File Name					:		Log.h
 * > Author						:		soymuchacho
 * > Created Time				:		2015-10
 * > brief						:		日志 
 *
 * */

#ifndef SHARED_LOG_H
#define SHARED_LOG_H

#include <common/Singleton.h>
#include <common/Mutex.h>
#include <include/Common.h>
#include <list>

namespace Shared
{

enum LOGLEVEL
{
	LOG_INLIVID = 0,			// 空
	LOG_ERROR,					// 错误
	LOG_WORN,					// 警告
	LOG_RELEASE,				// 发布版本打印
	LOG_DEBUG,					// 调试版本打印
};

static void * ThreadWriteLog(void *);

class Log : public Singleton<Log>
{
    SINGLETON_PARENT_FRIEND(Log);
private:
	Log();
	~Log();
public:
	void Initialize(string,LOGLEVEL level);
	bool new_log_file(char *appname);
	void Release();
	void Write(LOGLEVEL level,const char * type,const char * fn,int line,const char * fmt,...);
	void WriteLog(LOGLEVEL level,const char * type,const char * type1,const char * idtype,unsigned int id,const char * fmt, ...);
	void WriteData(LOGLEVEL level,unsigned char * data,unsigned int size);
public:
	string GetTimestamp();
	void OutTime(FILE * stream);
	void OutTimestamp(FILE * file);
public:
	void WriteTask(string & s);
	void AddWriteTask(string & s);
	bool GetWriteTask(string & s);
private:
	FILE			*logFile; 
	int				log_file_lines;	
	LOGLEVEL		log_level;
	string			fn;
	string			path;
	mutable Mutex	m_mutex;
private:
	list< string >	m_list;
};

static inline Log & Shared_Log()
{
	return Log::getSingleton();
}

}// END NAMESPACE

#define SharedLog Shared::Shared_Log()

// 二进制打印
#define LOGDATA(data,size) \
	Shared::Shared_Log().WriteData(Shared::LOG_DEBUG,(unsigned char *)(data),size)

#define LOGDEBUG(type,fmt, ...) \
	Shared::Shared_Log().Write(Shared::LOG_DEBUG,type,__FILE__,__LINE__,fmt,##__VA_ARGS__)

#define LOGDWORN(type,fmt,...) \
	Shared::Shared_Log().Write(Shared::LOG_WORN,type,__FILE__,__LINE__,fmt,##__VA_ARGS__)

#define LOGERROR(type,fmt,...) \
	Shared::Shared_Log().Write(Shared::LOG_ERROR,__FILE__,__LINE__,fmt,##__VA_ARGS__)

#define LOG(type,type1,idtype,id,fmt,...) \
	Shared::Shared_Log().WriteLog(Shared::LOG_RELEASE,type,type1,idtype,id,fmt,##__VA_ARGS__)

#define LOG2(type,type1,fmt,...) \
	Shared::Shared_Log().WriteLog(Shared::LOG_RELEASE,type,type1,"",0,fmt,##__VA_ARGS__)

#define OUTPUT(type,fmt, ...) \
    Shared::Shared_Log().Write(Shared::LOG_RELEASE,type,__FILE__,__LINE__,fmt,##__VA_ARGS__)
#endif// END SHARED_LOG_H
