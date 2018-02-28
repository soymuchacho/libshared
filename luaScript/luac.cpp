//////////////////////////////////////////////////////////////////////
//	created:	2018/02/22
//	filename: 	CommonShare/luac.cpp
//	author:		vesper	
//	
///	purpose:	
//////////////////////////////////////////////////////////////////////
#include <luac.h>
#include "Log.h"

namespace LuaC
{


CLuaInt64::CLuaInt64(const std::string& a_data)
: m_data(0)
{
	setData(a_data);
}

CLuaInt64 CLuaInt64::operator /(const CLuaInt64& a_data) const 
{ 
	if (a_data.m_data == 0){
		return 0;
	}
	return CLuaInt64(m_data / a_data.m_data);
}

CLuaInt64 CLuaInt64::operator /(int a_data) const 
{ 
	if (a_data == 0){
		return 0;
	}
	return CLuaInt64(m_data / a_data);
}

CLuaInt64 CLuaInt64::operator /(long long a_data) const
{
	if (a_data == 0){
		return 0;
	}
	return CLuaInt64(m_data / a_data);
}

CLuaInt64 CLuaInt64::operator /(float a_data) const 
{
	if (a_data == 0){
		return 0;
	}
	return CLuaInt64(m_data / (long long)a_data); 
}

CLuaInt64& CLuaInt64::operator /=(const CLuaInt64& a_data) 
{ 
	if (a_data.m_data == 0){
		return *this;
	}
	m_data /= a_data.m_data; 
	return *this; 
}

CLuaInt64& CLuaInt64::operator /=(int a_data) 
{
	if (a_data == 0){
		return *this;
	}
	m_data /= a_data; 
	return *this; 
}

CLuaInt64& CLuaInt64::operator /=(long long a_data)
{
	if (a_data == 0){
		return *this;
	}
	m_data /= a_data; 
	return *this; 
}

CLuaInt64& CLuaInt64::operator /=(float a_data) 
{ 
	if (a_data == 0){
		return *this;
	}
	m_data /= (long long)a_data;
	return *this; 
}

void CLuaInt64::setData(int a_data)
{
	m_data = (long long)a_data;
}

void CLuaInt64::setData(float a_data)
{
	m_data = (long long)a_data;
}

void CLuaInt64::setData(long long a_data)
{
	m_data = (long long)a_data;
}

void CLuaInt64::setData(const CLuaInt64& a_data)
{
	m_data = a_data.m_data;
}

void CLuaInt64::setData(const std::string& a_data)
{

#ifdef _WIN32

	m_data = (long long)_strtoi64(a_data.c_str(), NULL, 10);

#else

	m_data = atoll(a_data.c_str());

#endif
}

std::string CLuaInt64::toString(char a_type) const
{
	std::string temp;
	char buf[256] = {0};
	switch (a_type)
	{
	case 'h':
		sprintf(buf,"%llx", m_data);
		temp = buf;
		//temp.format("%llx", m_data);
		break;
	case 'H':
		sprintf(buf,"%llX", m_data);
		temp = buf;
		//temp.format("%llX", m_data);
		break;
	case 'o':
	case 'O':
		sprintf(buf,"%llu", m_data);
		temp = buf;
		//temp.format("%llu", m_data);
		break;
	case 'd':
	case 'D':
	default:
		sprintf(buf,"%lld", m_data);
		temp = buf;
		//temp.format("%lld", m_data);
	}
	
	return temp;
}

const std::string& CLuaInt64::getLuaUserType()
{
	static std::string temp = "LuaC::CLuaInt64";
	return temp;
}

long long CLuaInt64::getData() const
{ 
	return m_data; 
}

void luaLogDebug(std::string strText)
{
	LOGDEBUG("debug",strText.c_str());
}

void luaLogError(std::string strText)
{
	LOGDEBUG("debug",strText.c_str());
}


}//LuaC

