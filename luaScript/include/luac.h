//////////////////////////////////////////////////////////////////////
//	created:	2018/02/22
//	filename: 	luaScript\luac.h
//	author:		vesper
//	
///	purpose:	
//////////////////////////////////////////////////////////////////////
#ifndef __LUASCRIPT_LUAC_H__
#define __LUASCRIPT_LUAC_H__

#include <luaUserData.h>
#include <vector>

namespace LuaC
{

template<class TYPE>
class CLuaList
{
public:
	virtual ~CLuaList(){}

	virtual void clear()
	{
		m_list.clear();
	}

	void addItem(const TYPE& a_item)
	{
		m_list.push_back(a_item);
	}

	int getSize() const
	{
		return (int)m_list.size();
	}

	TYPE& operator [](int a_index)
	{
		if (a_index <= 0 ){
			throw "下标越界";
		}
		if (a_index > (int)m_list.size()){
			throw "下标越界";
		}
		return m_list[a_index-1];
	}

	const TYPE& operator [](int a_index) const
	{
		if (a_index <= 0 ){
			throw "下标越界";
		}
		if (a_index > (int)m_list.size()){
			throw "下标越界";
		}
		return m_list[a_index-1];
	}
protected:
	std::vector<TYPE> m_list;
};

class CLuaInt64 : public LuaScript::CLuaUserData
{
public:
	CLuaInt64() : m_data(0) {}
	CLuaInt64(int a_data) : m_data(a_data) {}
	CLuaInt64(float a_data) : m_data((long long)a_data) {}
	CLuaInt64(long long a_data) : m_data(a_data) {}
	CLuaInt64(const CLuaInt64& a_data) : m_data(a_data.m_data) {}
	CLuaInt64(const std::string& a_data);

	~CLuaInt64(){}

	CLuaInt64 operator +(const CLuaInt64& a_data) const { return CLuaInt64(m_data + a_data.m_data); } 
	CLuaInt64 operator -(const CLuaInt64& a_data) const { return CLuaInt64(m_data - a_data.m_data); }
	CLuaInt64 operator *(const CLuaInt64& a_data) const { return CLuaInt64(m_data * a_data.m_data); }
	CLuaInt64 operator /(const CLuaInt64& a_data) const;

	CLuaInt64 operator +(int a_data) const { return CLuaInt64(m_data + a_data); }
	CLuaInt64 operator -(int a_data) const { return CLuaInt64(m_data - a_data); }
	CLuaInt64 operator *(int a_data) const { return CLuaInt64(m_data * a_data); }
	CLuaInt64 operator /(int a_data) const;

	CLuaInt64 operator +(long long a_data) const { return CLuaInt64(m_data + a_data); }
	CLuaInt64 operator -(long long a_data) const { return CLuaInt64(m_data - a_data); }
	CLuaInt64 operator *(long long a_data) const { return CLuaInt64(m_data * a_data); }
	CLuaInt64 operator /(long long a_data) const;

	CLuaInt64 operator +(float a_data) const { return CLuaInt64(m_data + (long long)a_data);}
	CLuaInt64 operator -(float a_data) const { return CLuaInt64(m_data - (long long)a_data);}
	CLuaInt64 operator *(float a_data) const { return CLuaInt64(m_data * (long long)a_data);}
	CLuaInt64 operator /(float a_data) const;

	CLuaInt64& operator +=(const CLuaInt64& a_data) { m_data += a_data.m_data; return *this; }
	CLuaInt64& operator -=(const CLuaInt64& a_data) { m_data -= a_data.m_data; return *this; }
	CLuaInt64& operator *=(const CLuaInt64& a_data) { m_data*= a_data.m_data; return *this; }
	CLuaInt64& operator /=(const CLuaInt64& a_data);

	CLuaInt64& operator +=(int a_data) { m_data += a_data; return *this; }
	CLuaInt64& operator -=(int a_data) { m_data -= a_data; return *this; }
	CLuaInt64& operator *=(int a_data) { m_data *= a_data; return *this; }
	CLuaInt64& operator /=(int a_data);

	CLuaInt64& operator +=(long long a_data) { m_data += a_data; return *this; }
	CLuaInt64& operator -=(long long a_data) { m_data -= a_data; return *this; }
	CLuaInt64& operator *=(long long a_data) { m_data *= a_data; return *this; }
	CLuaInt64& operator /=(long long a_data);

	CLuaInt64& operator +=(float a_data) { m_data += (long long)a_data; return *this; }
	CLuaInt64& operator -=(float a_data) { m_data -= (long long)a_data; return *this; }
	CLuaInt64& operator *=(float a_data) { m_data *= (long long)a_data; return *this; }
	CLuaInt64& operator /=(float a_data);

	bool operator >(const CLuaInt64& a_data) const { return m_data > a_data.m_data; }
	bool operator >(int a_data) const { return m_data > a_data; }
	bool operator >(long long a_data) const { return m_data > a_data; }
	bool operator >(float a_data) const { return m_data > (long long)a_data; }

	bool operator >=(const CLuaInt64& a_data) const { return m_data >= a_data.m_data; }
	bool operator >=(int a_data) const { return m_data >= a_data; }
	bool operator >=(long long a_data) const { return m_data >= a_data; }
	bool operator >=(float a_data) const { return m_data >= (long long)a_data; }

	bool operator <(const CLuaInt64& a_data) const { return m_data < a_data.m_data; }
	bool operator <(int a_data) const { return m_data < a_data; }
	bool operator <(long long a_data) const { return m_data < a_data; }
	bool operator <(float a_data) const { return m_data < (long long)a_data; }

	bool operator <=(const CLuaInt64& a_data) const { return m_data <= a_data.m_data; }
	bool operator <=(int a_data) const { return m_data <= a_data; }
	bool operator <=(long long a_data) const { return m_data <= a_data; }
	bool operator <=(float a_data) const { return m_data <= (long long)a_data; }

	CLuaInt64& operator =(const CLuaInt64& a_data) {  m_data = a_data.m_data; return *this; }
	CLuaInt64& operator =(int a_data) {  m_data = a_data; return *this; }
	CLuaInt64& operator =(long long a_data) {  m_data = a_data; return *this; }
	CLuaInt64& operator =(float a_data) {  m_data = (long long)a_data; return *this; }

	bool operator ==(const CLuaInt64& a_data) const { return m_data == a_data.m_data; }
	bool operator ==(int a_data) const { return m_data == a_data; }
	bool operator ==(long long a_data) const { return m_data == a_data; }
	bool operator ==(float a_data) const { return m_data == (long long)a_data; }

	bool operator !=(const CLuaInt64& a_data) const { return m_data != a_data.m_data; }
	bool operator !=(int a_data) const { return m_data != a_data; }
	bool operator !=(long long a_data) const{ return m_data != a_data; }
	bool operator !=(float a_data) const{ return m_data != (long long)a_data; }

	void setData(int a_data);
	void setData(float a_data);
	void setData(long long a_data);
	void setData(const CLuaInt64& a_data);
	void setData(const std::string& a_data);

	std::string toString(char a_type = 'd') const;

public:
	virtual const std::string& getLuaUserType();
	long long getData() const;

private:
	long long m_data;
};

class CLuaIntList : public CLuaList<int>
{
public:
	CLuaIntList() {}
	CLuaIntList(unsigned int a_size) { m_list.resize(a_size, 0); }
	~CLuaIntList() {}
};

class CLuaStringList : public CLuaList<std::string>
{
public:
	CLuaStringList() {}
	CLuaStringList(unsigned int a_size) { m_list.resize(a_size, ""); }
	~CLuaStringList() {}
};


void luaLogDebug(std::string strText);

}//LuaC

#endif//__BSLIB_LUASCRIPT_LUAC_H__

