/**
 *	> Copyright(c) 2015 guqi
 *
 *	> LIBSHARED  VERSION :		0.0.1 
 *
 *	> File Name			 :		my_func.h
 *
 *	> Author			 :		guqi
 *
 *	> Mail				 :		guqi_282@126.com
 *
 *	> Created Time		 :		2015-10
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
