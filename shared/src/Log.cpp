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
 * > File Name					:		Log.cpp
 * > Author						:		soymuchacho
 * > Created Time				:		2015-10
 * > brief						:		日志
 *
 * */

#include <common/Log.h>
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
//	Initialize("OutPut",LOG_DEBUG);
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
