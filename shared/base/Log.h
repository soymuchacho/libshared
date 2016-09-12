/**
 *	> Copyright(c) 2015 guqi
 *
 *	> LIBSHARED  VERSION :		0.0.1 
 *
 *	> File Name			 :		Log.h
 *
 *	> Author			 :		guqi
 *
 *	> Mail				 :		guqi_282@126.com
 *
 *	> Created Time		 :		2015-10
 *
 * */

#ifndef SHARED_LOG_H
#define SHARED_LOG_H

#include <base/Singleton.h>
#include <base/Mutex.h>
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
	friend class Singleton< Log >;
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

	string GetTimestamp();
	void OutTime(FILE * stream);
	void OutTimestamp(FILE * file);
public:
	void WriteTask(string & s);
	void AddWriteTask(string & s);
	bool GetWriteTask(string & s);
private:
	mutable Mutex	m_mutex;
	FILE			*logFile; 
	int				log_file_lines;	
	LOGLEVEL		log_level;
	string			fn;
	string			path;
private:
	list< string >	m_list;
};

static inline Log & Shared_Log()
{
	return Log::getSingleton();
}

}// END NAMESPACE

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

#endif// END SHARED_LOG_H
