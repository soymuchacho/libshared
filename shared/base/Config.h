/**
 *	> Copyright(c) 2015 guqi
 *
 *	> LIBSHARED  VERSION :		0.0.1 
 *
 *	> File Name			 :		Config.h
 *
 *	> Author			 :		guqi
 *
 *	> Mail				 :		guqi_282@126.com
 *
 *	> Created Time		 :		2015-10
 *
 * */

#ifndef SHARED_CONFIG_H
#define SHARED_CONFIG_H

#include "Singleton.h"
#include <map>
#include <string>
using namespace std;

namespace Shared
{

class Config : public Singleton< Config >
{
	friend class Singleton< Config >;
private:
	Config();
	~Config();
public:
	void Initialize(const char * path);
	int GetIntValue(const char * szKey);
	void GetStringValue(const char * szKey,char * strValue,int size);
private:
	void Parse(string s);
private:
	map<string,string> m_map;
};

static inline Config & Shared_Config()
{
	return Config::getSingleton();
}

}// END NAMESPACE

#endif// END SHARED_CONFIG_H
