//////////////////////////////////////////////////////////////////////
//	created:	2018/02/22
//	filename: 	CommonShare\luaState.cpp
//	author:		vesper	
//	
///	purpose:	
//////////////////////////////////////////////////////////////////////
#include <luaState.h>
#include <tolua++.h>
#include <luac.h>
#include "tolua_luac.h"

namespace LuaScript
{

CLuaState::CLuaState()
: m_luaState(NULL)
, m_functionState(0)
{
	;
}

CLuaState::~CLuaState()
{
	;
}

bool CLuaState::init()
{
	clear();

	m_luaState = lua_open();

	luaL_openlibs(m_luaState);
	if (!_init(m_luaState)){
		clear();
		return false;
	}
	return true;
}

void CLuaState::clear()
{
	if (m_luaState != NULL) {
		lua_close(m_luaState);
		m_luaState = NULL;
	}
}

bool CLuaState::executeFile(const std::string& a_filePath)
{
	if (m_luaState == NULL) {
		return false;
	}
	int status = luaL_loadfile(m_luaState, a_filePath.c_str());    
	if (status != 0){
		_outputError(status);
		//BSLIB_LOG_ERROR(ETT_BSLIB_LUA, "加载LUA文件[Name=%s]失败", a_filePath.c_str());
		return false;
	}
	status = lua_pcall(m_luaState, 0, LUA_MULTRET, 0);
	if (status != 0){
		_outputError(status);
		//BSLIB_LOG_ERROR(ETT_BSLIB_LUA, "加载LUA文件[Name=%s]失败", a_filePath.c_str());
		return false;
	}
	return true;
}

bool CLuaState::executeString(const std::string& a_luaScript)
{
	if (m_luaState == NULL) {
		return false;
	}
	int status = luaL_loadstring(m_luaState, a_luaScript.c_str());    
	if (status != 0){
		//BSLIB_LOG_ERROR(ETT_BSLIB_LUA, "加载LUA String[%s][Error=%d]失败", a_luaScript.c_str(), status);
		return false;
	}
	status = lua_pcall(m_luaState, 0, LUA_MULTRET, 0);
	if (status != 0){
		_outputError(status);
		//BSLIB_LOG_ERROR(ETT_BSLIB_LUA, "加载LUA String[%s][Error=%d]失败", a_luaScript.c_str(), status);
		return false;
	}
	return true;
}

bool CLuaState::executeBuffer(const void *buf, int bufSize)
{
	if (m_luaState == NULL) {
		return false;
	}
	int status = luaL_loadbuffer(m_luaState, (const char *)buf, (size_t)bufSize, (const char *)buf);    
	if (status != 0){
		//BSLIB_LOG_ERROR(ETT_BSLIB_LUA, "加载LUA Buffer[Error=%d]失败", status);
		return false;
	}
	status = lua_pcall(m_luaState, 0, LUA_MULTRET, 0);
	if (status != 0){
		_outputError(status);
		//BSLIB_LOG_ERROR(ETT_BSLIB_LUA, "加载LUA Buffer[Error=%d]失败", status);
		return false;
	}
	return true;
}

bool CLuaState::setGlobalData(const std::string& a_name)
{
	if (m_luaState == NULL || a_name.empty()){
		return false;
	}
	try{
		_pushData();
		lua_setglobal(m_luaState, a_name.c_str());
	} catch (...){
		//BSLIB_LOG_ERROR(ETT_BSLIB_LUA, "赋值LUA[Name=%s]失败", a_name.c_str());
		return false;
	}
	return true;
}

bool CLuaState::setGlobalData(const std::string& a_name, int a_value)
{
	if (m_luaState == NULL || a_name.empty()){
		return false;
	}
	try{
		_pushData(a_value);
		lua_setglobal(m_luaState, a_name.c_str());
	} catch (...){
		//BSLIB_LOG_ERROR(ETT_BSLIB_LUA, "赋值LUA[Name=%s]失败", a_name.c_str());
		return false;
	}
	return true;
}

bool CLuaState::setGlobalData(const std::string& a_name, float a_value)
{
	if (m_luaState == NULL || a_name.empty()){
		return false;
	}
	try{
		_pushData(a_value);
		lua_setglobal(m_luaState, a_name.c_str());
	} catch (...){
		//BSLIB_LOG_ERROR(ETT_BSLIB_LUA, "赋值LUA[Name=%s]失败", a_name.c_str());
		return false;
	}
	return true;
}

bool CLuaState::setGlobalData(const std::string& a_name, double a_value)
{
	if (m_luaState == NULL || a_name.empty()){
		return false;
	}
	try{
		_pushData(a_value);
		lua_setglobal(m_luaState, a_name.c_str());
	} catch (...){
		//BSLIB_LOG_ERROR(ETT_BSLIB_LUA, "赋值LUA[Name=%s]失败", a_name.c_str());
		return false;
	}
	return true;
}


bool CLuaState::setGlobalData(const std::string& a_name, bool a_value)
{
	if (m_luaState == NULL || a_name.empty()){
		return false;
	}
	try{
		_pushData(a_value);
		lua_setglobal(m_luaState, a_name.c_str());
	} catch (...){
		//BSLIB_LOG_ERROR(ETT_BSLIB_LUA, "赋值LUA[Name=%s]失败", a_name.c_str());
		return false;
	}
	return true;
}


bool CLuaState::setGlobalData(const std::string& a_name, const std::string& a_value)
{
	if (m_luaState == NULL || a_name.empty()){
		return false;
	}
	try{
		_pushData(a_value);
		lua_setglobal(m_luaState, a_name.c_str());
	} catch (...){
		//BSLIB_LOG_ERROR(ETT_BSLIB_LUA, "赋值LUA[Name=%s]失败", a_name.c_str());
		return false;
	}
	return true;
}

bool CLuaState::setGlobalData(const std::string& a_name, void* a_value)
{
	if (m_luaState == NULL || a_name.empty()){
		return false;
	}
	try{
		_pushData(a_value);
		lua_setglobal(m_luaState, a_name.c_str());
	} catch (...){
		//BSLIB_LOG_ERROR(ETT_BSLIB_LUA, "赋值LUA[Name=%s]失败", a_name.c_str());
		return false;
	}
	return true;
}

bool CLuaState::getGlobalData(const std::string& a_name)
{
	if (m_luaState == NULL || a_name.empty()){
		return false;
	}
	try{
		lua_getglobal(m_luaState, a_name.c_str());
		bool isNil = lua_isnil(m_luaState, -1);
		if (isNil) {
			_popData();
			return true;
		}
	} catch (...){
		//BSLIB_LOG_ERROR(ETT_BSLIB_LUA, "获得LUA[Name=%s]失败", a_name.c_str());
	}
	return false;
}

bool CLuaState::getGlobalData(const std::string& a_name, int& a_value)
{
	if (m_luaState == NULL || a_name.empty()){
		return false;
	}
	try{
		lua_getglobal(m_luaState, a_name.c_str());
		bool typeMatch = lua_type(m_luaState, -1) == LUA_TNUMBER;
		if (typeMatch) {
			_popData(a_value);
			return true;
		}
	} catch (...){
		//BSLIB_LOG_ERROR(ETT_BSLIB_LUA, "获得LUA[Name=%s]失败", a_name.c_str());
	}
	return false;
}

bool CLuaState::getGlobalData(const std::string& a_name, float& a_value)
{
	if (m_luaState == NULL || a_name.empty()){
		return false;
	}
	try{
		lua_getglobal(m_luaState, a_name.c_str());
		bool typeMatch = lua_type(m_luaState, -1) == LUA_TNUMBER;
		if (typeMatch) {
			_popData(a_value);
			return true;
		}
	} catch (...){
		//BSLIB_LOG_ERROR(ETT_BSLIB_LUA, "获得LUA[Name=%s]失败", a_name.c_str());
	}
	return false;
}

bool CLuaState::getGlobalData(const std::string& a_name, double& a_value)
{
	if (m_luaState == NULL || a_name.empty()){
		return false;
	}
	try{
		lua_getglobal(m_luaState, a_name.c_str());
		bool typeMatch = lua_type(m_luaState, -1) == LUA_TNUMBER;
		if (typeMatch) {
			_popData(a_value);
			return true;
		}
	} catch (...){
		//BSLIB_LOG_ERROR(ETT_BSLIB_LUA, "获得LUA[Name=%s]失败", a_name.c_str());
	}
	return false;
}

bool CLuaState::getGlobalData(const std::string& a_name, bool& a_value)
{
	if (m_luaState == NULL || a_name.empty()){
		return false;
	}
	try{
		lua_getglobal(m_luaState, a_name.c_str());
		bool typeMatch = lua_type(m_luaState, -1) == LUA_TBOOLEAN;
		if (typeMatch) {
			_popData(a_value);
			return true;
		}
	} catch (...){
		//BSLIB_LOG_ERROR(ETT_BSLIB_LUA, "获得LUA[Name=%s]失败", a_name.c_str());
	}
	return false;
}

bool CLuaState::getGlobalData(const std::string& a_name, std::string& a_value)
{
	if (m_luaState == NULL || a_name.empty()){
		return false;
	}
	try{
		lua_getglobal(m_luaState, a_name.c_str());
		bool typeMatch = lua_type(m_luaState, -1) == LUA_TSTRING;
		if (typeMatch) {
			_popData(a_value);
			return true;
		}
	} catch (...){
		//BSLIB_LOG_ERROR(ETT_BSLIB_LUA, "获得LUA[Name=%s]失败", a_name.c_str());
	}
	return false;
}

bool CLuaState::getGlobalData(const std::string& a_name, void*& a_value)
{
	if (m_luaState == NULL || a_name.empty()){
		return false;
	}
	try{
		lua_getglobal(m_luaState, a_name.c_str());
		bool typeMatch = lua_type(m_luaState, -1) == LUA_TLIGHTUSERDATA;
		if (typeMatch) {
			_popData(a_value);
			return true;
		}
	} catch (...){
		//BSLIB_LOG_ERROR(ETT_BSLIB_LUA, "获得LUA[Name=%s]失败", a_name.c_str());
	}
	return false;
}

int CLuaState::getGlobalInt32(const std::string& a_name)
{
	int data = 0;
	if (!getGlobalData(a_name, data)){
		//BSLIB_LOG_ERROR(ETT_BSLIB_LUA, "获得LUA[Name=%s]失败", a_name.c_str());
		return data;
	}
	return data;
}

float CLuaState::getGlobalFloat(const std::string& a_name)
{
	float data = 0;
	if (!getGlobalData(a_name, data)){
		//BSLIB_LOG_ERROR(ETT_BSLIB_LUA, "获得LUA[Name=%s]失败", a_name.c_str());
		return data;
	}
	return data;
}

double CLuaState::getGlobalDouble(const std::string& a_name)
{
	double data = 0;
	if (!getGlobalData(a_name, data)){
		//BSLIB_LOG_ERROR(ETT_BSLIB_LUA, "获得LUA[Name=%s]失败", a_name.c_str());
		return data;
	}
	return data;
}

bool CLuaState::getGlobalBoolean(const std::string& a_name)
{
	bool data = 0;
	if (!getGlobalData(a_name, data)){
		//BSLIB_LOG_ERROR(ETT_BSLIB_LUA, "获得LUA[Name=%s]失败", a_name.c_str());
		return data;
	}
	return data;
}

std::string CLuaState::getGlobalString(const std::string& a_name)
{
	std::string data = "";
	if (!getGlobalData(a_name, data)){
		//BSLIB_LOG_ERROR(ETT_BSLIB_LUA, "获得LUA[Name=%s]失败", a_name.c_str());
		return data;
	}
	return data;
}

void* CLuaState::getGlobalPointer(const std::string& a_name)
{
	void* data = NULL;
	if (!getGlobalData(a_name, data)){
		//BSLIB_LOG_ERROR(ETT_BSLIB_LUA, "获得LUA[Name=%s]失败", a_name.c_str());
		return data;
	}
	return data;
}

bool CLuaState::_beginCallFunction(const std::string& a_name)
{
	if (m_luaState == NULL || a_name.empty()){
		return false;
	}
	lua_getglobal(m_luaState, a_name.c_str());
	_setFunctionName(a_name);
	m_functionState = 0;

	return true;
}

bool CLuaState::_endCallFunction()
{
	int index = lua_gettop(m_luaState);
	int status = lua_pcall(m_luaState, index - 1, 0, 0);
	if (status == 0){
		return true;
	}
	_outputError(status);
	return false;
}

bool CLuaState::_endCallFunction(int& a_resultValue)
{
	int index = lua_gettop(m_luaState);
	int status = lua_pcall(m_luaState, index - 1, 1, 0);
	if (status == 0){
		_popData(a_resultValue);
		return true;
	}
	_outputError(status);
	return false;
}

bool CLuaState::_endCallFunction(float& a_resultValue)
{
	int index = lua_gettop(m_luaState);
	int status = lua_pcall(m_luaState, index - 1, 1, 0);
	if (status == 0){
		_popData(a_resultValue);
		return true;
	}
	_outputError(status);
	return false;
}

bool CLuaState::_endCallFunction(double& a_resultValue)
{
	int index = lua_gettop(m_luaState);
	int status = lua_pcall(m_luaState, index - 1, 1, 0);
	if (status == 0){
		_popData(a_resultValue);
		return true;
	}
	_outputError(status);
	return false;
}

bool CLuaState::_endCallFunction(bool& a_resultValue)
{
	int index = lua_gettop(m_luaState);
	int status = lua_pcall(m_luaState, index - 1, 1, 0);
	if (status == 0){
		_popData(a_resultValue);
		return true;
	}
	_outputError(status);
	return false;
}

bool CLuaState::_endCallFunction(std::string& a_resultValue)
{
	int index = lua_gettop(m_luaState);
	int status = lua_pcall(m_luaState, index - 1, 1, 0);
	if (status == 0){
		_popData(a_resultValue);
		return true;
	}
	_outputError(status);
	return false;
}

bool CLuaState::_endCallFunction(void*& a_resultValue)
{
	int index = lua_gettop(m_luaState);
	int status = lua_pcall(m_luaState, index - 1, 1, 0);
	if (status == 0){
		_popData(a_resultValue);
		return true;
	}
	_outputError(status);
	return false;
}

bool CLuaState::_endCallFunction(CLuaUserData*& a_resultValue)
{
	int index = lua_gettop(m_luaState);
	int status = lua_pcall(m_luaState, index - 1, 1, 0);
	if (status == 0){
		_popData(a_resultValue);
		return true;
	}
	_outputError(status);
	return false;
}

void CLuaState::_pushParam()
{
	_pushData();
}

void CLuaState::_pushParam(int a_value)
{
	_pushData(a_value);
}

void CLuaState::_pushParam(float a_value)
{
	_pushData(a_value);
}

void CLuaState::_pushParam(double a_value)
{
	_pushData(a_value);
}

void CLuaState::_pushParam(bool a_value)
{
	_pushData(a_value);
}

void CLuaState::_pushParam(const std::string& a_value)
{
	_pushData(a_value);
}

void CLuaState::_pushParam(void* a_value)
{
	_pushData(a_value);
}

void CLuaState::_pushParam(CLuaUserData* a_value)
{
	_pushData(a_value);
}

void CLuaState::_pushData()
{
	lua_pushnil(m_luaState);
}

void CLuaState::_pushData(int a_value)
{
	lua_pushinteger(m_luaState, a_value);
}

void CLuaState::_pushData(float a_value)
{
	lua_pushnumber(m_luaState, a_value);
}

void CLuaState::_pushData(double a_value)
{
	lua_pushnumber(m_luaState, a_value);
}

void CLuaState::_pushData(bool a_value)
{
	lua_pushboolean(m_luaState, (int)a_value);
}

void CLuaState::_pushData(const std::string& a_value)
{
	lua_pushstring(m_luaState, a_value.c_str());
}

void CLuaState::_pushData(void* a_value)
{
	lua_pushlightuserdata(m_luaState, a_value);
}

void CLuaState::_pushData(CLuaUserData* a_value)
{
	if (a_value == NULL){
		lua_pushlightuserdata(m_luaState, a_value);
		return;
	}
	tolua_pushusertype(m_luaState, a_value, a_value->getLuaUserType().c_str());
}

void CLuaState::_popData()
{
	lua_pop(m_luaState, 1);
}

void CLuaState::_popData(int& a_value)
{
	a_value = (int)lua_tonumber(m_luaState, -1);
	lua_pop(m_luaState, 1);
}

void CLuaState::_popData(float& a_value)
{
	a_value = (float)lua_tonumber(m_luaState, -1);
	lua_pop(m_luaState, 1);
}

void CLuaState::_popData(double& a_value)
{
	a_value = (double)lua_tonumber(m_luaState, -1);
	lua_pop(m_luaState, 1);
}

void CLuaState::_popData(bool& a_value)
{
	a_value = lua_toboolean(m_luaState, -1) != 0;
	lua_pop(m_luaState, 1);
}

void CLuaState::_popData(std::string& a_value)
{
	const char *data = lua_tostring(m_luaState, -1);
	if (data == NULL) {
		a_value = "";
	} else {
		a_value = data;
	}
	lua_pop(m_luaState, 1);
}

void CLuaState::_popData(void*& a_value)
{
	a_value = lua_touserdata(m_luaState, -1);
	lua_pop(m_luaState, 1);
}

void CLuaState::_popData(CLuaUserData*& a_value)
{
	a_value = (CLuaUserData*)tolua_tousertype(m_luaState, -1, 0);
	lua_pop(m_luaState, 1);
}

bool CLuaState::_init(lua_State* a_luaState)
{
	tolua_open(a_luaState);
	tolua_luac_open(a_luaState);
	return true;
}

void CLuaState::_outputError(int a_errorStatus)
{
	if (a_errorStatus == 0){
		return ;
	}
	_setFunctionState(a_errorStatus);

	std::string errorStr;
	_popData(errorStr);

	//BSLIB_LOG_ERROR(ETT_BSLIB_LUA, "LUA错误提示[CallFunctionName=%s][Error=%d][%s]失败", m_functionName.c_str(), a_errorStatus, errorStr.c_str());
}

}//LuaScript


