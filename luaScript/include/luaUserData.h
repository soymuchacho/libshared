//////////////////////////////////////////////////////////////////////
//	created:	2018/02/22
//	filename: 	luaScript\luaUserData.h
//	author:		vesper	
//	
///	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __LUASCRIPT_LUAUSERDATA_H__
#define __LUASCRIPT_LUAUSERDATA_H__

#include <string>

namespace LuaScript
{

class CLuaUserData
{
public:
	virtual ~CLuaUserData(){}
	virtual const std::string& getLuaUserType() = 0;
};

}//LuaScript


#endif//__LUASCRIPT_LUAC_H__

