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
 * > File Name					:		my_func.h
 * > Author						:		soymuchacho
 * > Created Time				:		2015-10
 * > brief						:		something
 *
 * */


#ifndef SHARED_MY_FUNC_H
#define SHARED_MY_FUNC_H

#include <cctype>
#include <iostream>
#include <algorithm>
using namespace std;

namespace Shared
{

// 字符串去除空格
inline string & trim(string & str)
{
	if(str.empty())
	{
		return str;
	}
	str.erase(0,str.find_first_not_of("\t"));
	str.erase(0,str.find_first_not_of(" "));
	str.erase(str.find_last_not_of("\t")+1);
	str.erase(str.find_last_not_of(" ")+1);
	return str;
}

inline void trim(char * str)
{
	if(str == NULL)
		return;
	int size = strlen(str);
	char * start = str;
	for(int i = size; i > 0;i--)
	{
		if(start[i - 1] != ' ' && start[i - 1] != '\t' && start[i - 1] != '\n')
		{
			break;
		}
		start[i - 1] = '\0';
	}
	size = strlen(str);
	int j = 0;
	bool begin = false;
	for(int i = 0; i <= size; i++)
	{
		if(begin == false)
		{
			if(start[i] != ' ' && start[i] != '\t' && start[i] != '\n')
			{
				begin = true;
				if(i == 0)
					return;
			}
		}
		else
		{
			start[j] = start[i-1];
			j++;
		}
	}
	start[j] = '\0';
}

}
#endif
