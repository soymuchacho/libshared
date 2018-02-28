//////////////////////////////////////////////////////////////////////
//	created:	2018/02/22
//	filename: 	luaScript\baseDef.h
//	author:		vesper	
//	
///	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __LUASCRIPT_BASEDEF_H__
#define __LUASCRIPT_BASEDEF_H__

#include <iostream>
#include <string>

extern "C" 
{ 

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

};

class CLuaUserData
{
public:
	CLuaUserData(){}
	virtual ~CLuaUserData(){}

	virtual const std::string& getLuaUserType() = 0;
};

#endif//__LUASCRIPT_BASEDEF_H__

