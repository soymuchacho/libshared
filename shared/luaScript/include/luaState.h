//////////////////////////////////////////////////////////////////////
//	created:	2018/02/22
//	filename: 	luaScript\luaState.h
//	author:		vesper
//	
///	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __LUASCRIPT_LUASTATE_H__
#define __LUASCRIPT_LUASTATE_H__

#include "baseDef.h"
#include "luaUserData.h"

namespace LuaScript
{

class CLuaState
{
public:
	CLuaState();
	virtual ~CLuaState();

	bool init();
	void clear();

	bool executeFile(const std::string& a_filePath);
	bool executeString(const std::string& a_luaScript);
	bool executeBuffer(const void *buf, int bufSize);

	// 设置Lua全局变量
	bool setGlobalData(const std::string& a_name);
	bool setGlobalData(const std::string& a_name, int a_value);
	bool setGlobalData(const std::string& a_name, float a_value);
	bool setGlobalData(const std::string& a_name, double a_value);
	bool setGlobalData(const std::string& a_name, bool a_value);
	bool setGlobalData(const std::string& a_name, const std::string& a_value);
	bool setGlobalData(const std::string& a_name, void* a_value);
	
	// 获得Lua全局变量
	bool getGlobalData(const std::string& a_name);
	bool getGlobalData(const std::string& a_name, int& a_value);
	bool getGlobalData(const std::string& a_name, float& a_value);
	bool getGlobalData(const std::string& a_name, double& a_value);
	bool getGlobalData(const std::string& a_name, bool& a_value);
	bool getGlobalData(const std::string& a_name, std::string& a_value);
	bool getGlobalData(const std::string& a_name, void*& a_value);

	int getGlobalInt32(const std::string& a_name);
	float getGlobalFloat(const std::string& a_name);
	double getGlobalDouble(const std::string& a_name);
	bool getGlobalBoolean(const std::string& a_name);
	std::string getGlobalString(const std::string& a_name);
	void* getGlobalPointer(const std::string& a_name);

	int getCallFunctionState() const { return m_functionState; }
protected:
	// Lua函数调用
	bool _beginCallFunction(const std::string& a_name); 

	bool _endCallFunction();
	bool _endCallFunction(int& a_resultValue);
	bool _endCallFunction(float& a_resultValue);
	bool _endCallFunction(double& a_resultValue);
	bool _endCallFunction(bool& a_resultValue);
	bool _endCallFunction(std::string& a_resultValue);
	bool _endCallFunction(void*& a_resultValue);
	bool _endCallFunction(CLuaUserData*& a_resultValue);

	// Lua函数调用参数设置
	void _pushParam();
	void _pushParam(int a_value);
	void _pushParam(float a_value);
	void _pushParam(double a_value);
	void _pushParam(bool a_value);
	void _pushParam(const std::string& a_value);
	void _pushParam(void* a_value);
	void _pushParam(CLuaUserData* a_value);

	void _pushData();
	void _pushData(int a_value);
	void _pushData(float a_value);
	void _pushData(double a_value);
	void _pushData(bool a_value);
	void _pushData(const std::string& a_value);
	void _pushData(void* a_value);
	void _pushData(CLuaUserData* a_value);

	void _popData();
	void _popData(int& a_value);
	void _popData(float& a_value);
	void _popData(double& a_value);
	void _popData(bool& a_value);
	void _popData(std::string& a_value);
	void _popData(void*& a_value);
	void _popData(CLuaUserData*& a_value);

	lua_State* _getLuaState() { return m_luaState; }
	void _setLuaState(lua_State* a_luaState) { m_luaState = a_luaState; }

protected:
	virtual bool _init(lua_State* a_luaState);

private:
	void _outputError(int a_errorStatus);
	void _setFunctionName(const std::string& a_name) { m_functionName = a_name; }
	const std::string& _getFunctionName() { return m_functionName; }
	void _setFunctionState(int a_functionState) { m_functionState = a_functionState; }

private:
	lua_State* m_luaState;
	int m_functionState;
	std::string m_functionName;
};

}//LuaScript

#endif//__LUASCRIPT_LUASTATE_H__

