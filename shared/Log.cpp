/**
 *	> Copyright(c) 2015 guqi
 *
 *	> LIBSHARED  VERSION :		0.0.1 
 *
 *	> File Name			 :		Log.cpp
 *
 *	> Author			 :		guqi
 *
 *	> Mail				 :		guqi_282@126.com
 *
 *	> Created Time		 :		2015-10
 *
 * */

#include <base/Log.h>
#include <dirent.h>
#include <pthread.h>
#include <string>
#include <iostream>
#include <sstream>
using namespace std;

namespace Shared
{

#define MAX_LOG_LINES 200000

initializeSingleton(Log);

Log::Log()
{
	logFile = NULL;
	Initialize("OutPut",LOG_DEBUG);
}

Log::~Log()
{

}

static void check_dir(char * thisdir)
{
	DIR * fdir;
	if( (fdir = opendir(thisdir)) == NULL)
		mkdir(thisdir,O_CREAT|S_IRUSR|S_IWUSR|S_IXUSR|S_IRGRP|S_IXGRP);
	closedir(fdir);
}

void check_log_dir(char * log_path)
{
	char thisdir[256] = {0};
	sprintf(thisdir,"%s",log_path);
	check_dir(thisdir);
}

void Log::Initialize(string logfn,LOGLEVEL level)
{
	fn = logfn;
	path = "./log";
	new_log_file((char *)logfn.c_str());
	
	log_level = level;
	
	pthread_t tid;
	if(pthread_create(&tid,NULL,ThreadWriteLog,NULL) == 0)
	{
		return;
	}
}

bool Log::new_log_file(char * appname)
{
	char tmpfn[256] = {0};
	
	check_log_dir((char *)path.c_str());
	
	time_t t = time(NULL);
	struct tm aTm;
	localtime_r(&t,&aTm);
	sprintf(tmpfn,"%s/%s_%02d-%02d-%02d_%02d:%02d:%02d",path.c_str(),appname,aTm.tm_year + 1900,aTm.tm_mon + 1,
			aTm.tm_mday,
			aTm.tm_hour,aTm.tm_min,aTm.tm_sec);	
	
	
	logFile = fopen(tmpfn,"w");
	if(logFile == NULL)
		return false;
	setbuf(logFile,NULL);
	log_file_lines = 0L;
	fprintf(logFile,"============================================ Server LOG ==================================\n");
	return true;
}

string Log::GetTimestamp()
{
	time_t t = time(NULL);
	struct tm aTm;
	char tstr[20] = {0};

	localtime_r(&t,&aTm);

	strftime(tstr,sizeof(tstr),"> %y-%m-%d_%H:%M:%S",&aTm);
	
	return string(tstr);
}

void Log::OutTime(FILE * stream)
{
	time_t t = time(NULL);
	struct tm aTm;
	
	localtime_r(&t,&aTm);
	fprintf(stream,"> %d-%02d-%02d %02d:%02d:%02d",aTm.tm_year + 1900,
			aTm.tm_mon + 1,aTm.tm_mday,aTm.tm_hour,aTm.tm_min,aTm.tm_sec);

}

void Log::OutTimestamp(FILE * file)
{
	time_t t = time(NULL);
	struct tm aTm;
	char tstr[20] = {0};
	
	localtime_r(&t,&aTm);
	strftime(tstr,sizeof(tstr),"> %y/%m/%d_%H:%M:%S",&aTm);
	fprintf(file,tstr);
}

void Log::Release()
{
	if(logFile != 0)
	{
		fclose(logFile);
		logFile = NULL;
		log_file_lines = 0;
	}
}

void Log::Write(LOGLEVEL level,const char * type,const char * file,int line,const char * fmt, ...)
{
	if(level > log_level)
		return;
	va_list ap;
	va_start(ap,fmt);

	ostringstream ostr;
	ostr << GetTimestamp() << " [" << type << "] ";
	
	char buf[512] = {0};
	
	vsprintf(buf,fmt,ap);
	
	ostr << buf << "\t\t" << file << ":" << line << endl;
	
	va_end(ap);
	string s = ostr.str();
	AddWriteTask(s);
}

void Log::WriteLog(LOGLEVEL level,const char * type,const char * type1,const char * idtype,unsigned int id,const char * fmt, ...)
{
	if(level > log_level)
		return;
	va_list ap;
	va_start(ap,fmt);

	ostringstream ostr;
	ostr << GetTimestamp() << " [" << type << "]"
		<< "[" << type1 << "] ";
	if(id != 0)
		ostr << " (" << idtype << " : " << id << ") ";
	
	char buf[512] = {0};
	
	vsprintf(buf,fmt,ap);
	
	ostr << buf << endl;
	
	va_end(ap);
	
	string s = ostr.str();
	AddWriteTask(s);
}

void Log::WriteData(LOGLEVEL level,unsigned char * data,unsigned int size)
{
	if(level > log_level)
		return;
	if(data == NULL)
		return;
	unsigned char * start = data;
	
	ostringstream ostr;

	for(int i = 0; i < size ; i++)
	{
		char buf[5] = {0};
		sprintf(buf,"%02x ",*(start + i));
		ostr << buf;
	}
	ostr << "\n";
	string s = ostr.str();
	AddWriteTask(s);
}

void Log::WriteTask(string & s)
{
	MutexLockGuard lock(&m_mutex);
	if(logFile)
	{
		if(log_file_lines >= MAX_LOG_LINES)
		{
			Release();
			new_log_file((char *)fn.c_str());
		}
		fprintf(logFile,"%s",s.c_str());
		fflush(logFile);
		log_file_lines++;
	}
	else
	{
		new_log_file((char *)fn.c_str());
	}
	printf("%s",s.c_str());
	fflush(stdout);
}

void Log::AddWriteTask(string & s)
{
	MutexLockGuard lock(&m_mutex);
	m_list.push_back(s);
	
	if( m_list.empty() )
	{
		m_list.clear();
	}
}

bool Log::GetWriteTask(string & s)
{
	MutexLockGuard lock(&m_mutex);
	if(m_list.empty())
		return false;
	list< string >::iterator itr;
	itr = m_list.begin();
	if(itr != m_list.end())
	{
		s = *itr;
		m_list.pop_front();
	}
	return true;
}

void * ThreadWriteLog(void * arg)
{
	pthread_detach(pthread_self());
	while(true)
	{
		string s;
		bool ret = Shared_Log().GetWriteTask(s);
		if(ret == true)
		{
			Shared_Log().WriteTask(s);
		}
		usleep(10);
	}
	return NULL;
}

}
