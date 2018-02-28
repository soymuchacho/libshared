//////////////////////////////////////////////////////////////////////
//	created:	2016/09/16
//	filename: 	BSLib\luaScript\luaScript.h
//	author:		mazhejiang
//	
///	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __LUASCRIPT_LUASCRIPT_H__
#define __LUASCRIPT_LUASCRIPT_H__

#include "luaState.h"


namespace LuaScript
{

class CLuaScript : public CLuaState
{
public:
	CLuaScript();
	virtual ~CLuaScript();

	template <class R>
	R callFunctionResult()
	{
		R ret;
		_endCallFunction(ret);
		return ret;
	}
	
	void callFunctionResult()
	{
		_endCallFunction();
	}
	
	void callFunction(const std::string& a_name)
	{
		_beginCallFunction(a_name);    
		return callFunctionResult();
	}
	
	template <class R>
	R callFunction(const std::string& a_name)
	{
		_beginCallFunction(a_name);    
		return callFunctionResult<R>();
	}
	
	template <class R, class P1>
	R callFunction(const std::string& a_name, const P1 &p1)
	{    
		_beginCallFunction(a_name);
		_pushParam(p1);
		return callFunctionResult<R>();
	}

	template <class R, class P1, class P2>
	R callFunction(const std::string& a_name, const P1 &p1, const P2 &p2)
	{    
		_beginCallFunction(a_name);
		_pushParam(p1);_pushParam(p2);
		return callFunctionResult<R>();
	}

	template <class R, class P1, class P2, class P3>
	R callFunction(const std::string& a_name, const P1 &p1, const P2 &p2, const P3 &p3)
	{    
		_beginCallFunction(a_name);
		_pushParam(p1);_pushParam(p2);_pushParam(p3);
		return callFunctionResult<R>();
	}

	template <class R, class P1, class P2, class P3, class P4>
	R callFunction(const std::string& a_name, const P1 &p1, const P2 &p2, const P3 &p3, const P4 &p4)
	{    
		_beginCallFunction(a_name);
		_pushParam(p1);_pushParam(p2);_pushParam(p3);_pushParam(p4);
		return callFunctionResult<R>();
	}

	template <class R, class P1, class P2, class P3, class P4, class P5>
	R callFunction(const std::string& a_name, const P1 &p1, const P2 &p2, const P3 &p3, const P4 &p4, const P5 &p5)
	{    
		_beginCallFunction(a_name);
		_pushParam(p1);_pushParam(p2);_pushParam(p3);_pushParam(p4);_pushParam(p5);
		return callFunctionResult<R>();
	}

	template <class R, class P1, class P2, class P3, class P4, class P5, class P6>
	R callFunction(const std::string& a_name, const P1 &p1, const P2 &p2, const P3 &p3, const P4 &p4, const P5 &p5, const P6 &p6)
	{    
		_beginCallFunction(a_name);
		_pushParam(p1);_pushParam(p2);_pushParam(p3);_pushParam(p4);_pushParam(p5);_pushParam(p6);
		return callFunctionResult<R>();
	}

	template <class R, class P1, class P2, class P3, class P4, class P5, class P6, class P7>
	R callFunction(const std::string& a_name, const P1 &p1, const P2 &p2, const P3 &p3, const P4 &p4, const P5 &p5, const P6 &p6, const P7 &p7)
	{    
		_beginCallFunction(a_name);
		_pushParam(p1);_pushParam(p2);_pushParam(p3);_pushParam(p4);_pushParam(p5);_pushParam(p6);_pushParam(p7);
		return callFunctionResult<R>();
	}

	template <class R, class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8>
	R callFunction(const std::string& a_name, const P1 &p1, const P2 &p2, const P3 &p3, const P4 &p4, const P5 &p5, const P6 &p6, const P7 &p7, const P8 &p8)
	{    
		_beginCallFunction(a_name);
		_pushParam(p1);_pushParam(p2);_pushParam(p3);_pushParam(p4);_pushParam(p5);_pushParam(p6);_pushParam(p7);_pushParam(p8);
		return callFunctionResult<R>();
	}

	template <class R, class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8, class P9>
	R callFunction(const std::string& a_name, const P1 &p1, const P2 &p2, const P3 &p3, const P4 &p4, const P5 &p5, const P6 &p6, const P7 &p7, const P8 &p8, const P9 &p9)
	{    
		_beginCallFunction(a_name);
		_pushParam(p1);_pushParam(p2);_pushParam(p3);_pushParam(p4);_pushParam(p5);_pushParam(p6);_pushParam(p7);_pushParam(p8);_pushParam(p9);
		return callFunctionResult<R>();
	}
};

}//LuaScript

#endif//__LUASCRIPT_LUASCRIPT_H__
