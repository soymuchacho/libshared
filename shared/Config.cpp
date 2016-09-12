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
 * > File Name					:		Config.cpp
 * > Author						:		soymuchacho
 * > Created Time				:		2015-10
 * > brief						:		配置文件 
 *
 * */

#include <base/Config.h>
#include <base/my_func.h>
#include <base/Log.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

namespace Shared
{

initializeSingleton( Config );

Config::Config()
{
	m_map.clear();
}

Config::~Config()
{

}

void Config::Initialize(const char * path)
{
	struct stat statbuff;
	int filesize = 0;
	
	if(stat(path,&statbuff) < 0)
	{
		return;
	}

	filesize = statbuff.st_size;
	
	int fileno;
	fileno = open(path,O_RDONLY);
	if(fileno < 0)
	{
		close(fileno);
		return ;
	}
	char * strTemp = new char[filesize];
	if(strTemp == NULL)
	{
		close(fileno);
		return;
	}
	string strConfig("");
	
	read(fileno,strTemp,filesize);
	strConfig.append(strTemp);	
	
	if(strTemp != NULL)
	{
		delete [] strTemp;
		strTemp = NULL;
	}
	//LOGDEBUG("debug","filesize = %d,string size = %d",filesize,strConfig.length());
	close(fileno);
	Parse(strConfig);
}

void Config::Parse(string s)
{
	int uIndex = 0;
	do
	{
		uIndex = s.find("\n");
		string str("");
		if(uIndex < 0)
		{
			if(s[0] == ' ')
			{
				if(s.size() <= 1)
					uIndex = -1;
				else
					uIndex = 1;
				continue;
			}
			else
				str = s;
		}
		else
		{
			str = s.substr(0,uIndex);
			s = s.substr(uIndex + 1);
			if(str[0] == ';' || str[0] == '\n' || str[0] == ' '|| str[0] == '[' || str[0] == '"')
			{	
				continue;
			}
		}
		
		int uIndex2 = 0;
		uIndex2 = str.find("=");
		if(uIndex2 < 0)
		{
			continue;
		}
		string s1,s2;
		s1 = str.substr(0,uIndex2);
		s2 = str.substr(uIndex2 + 1);
		int uIndex3 = s2.find("\r");
		if(uIndex3 > 0)
		{
			s2 = s2.substr(0,uIndex3);
		}
		s1 = trim(s1);
		s2 = trim(s2);
		m_map.insert(make_pair(s1,s2));
	}while(uIndex >= 0 && s.length() > 0);
}

int Config::GetIntValue(const char * strKey)
{
	map<string,string>::iterator itr;
	string s("");
	s.append(strKey);
	itr = m_map.find(strKey);
	if(itr != m_map.end())
	{
		//LOGDEBUG("debug","%s",itr->second.c_str());
		return strtoul(itr->second.c_str(),NULL,10);
	}
	return 0;
}

void Config::GetStringValue(const char * strKey,char * strValue,int size)
{
	if(strValue == NULL)
		return;
	memset(strValue,0,size);
	map<string,string>::iterator itr;
	string s("");
	s.append(strKey);
	itr = m_map.find(s);
	if(itr != m_map.end())
	{
		int byte = size > itr->second.length() ? itr->second.length() : size;
		//LOGDEBUG("debug","size %d copy byte %d",size,byte);
		strncpy(strValue,itr->second.c_str(),byte);
	}
}

}
