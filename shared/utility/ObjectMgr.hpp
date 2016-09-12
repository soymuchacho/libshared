/*!
 *	\brief  对象管理基类
 *
 *			Copyright(c) 2015 guqi。
 *
 *	\file		Object.hpp
 *
 *	\author		guqi_282@126.com
 *
 */
#ifndef UTILITY_OBJECT_MGR_H
#define UTILITY_OBJECT_MGR_H

#include <tr1/memory>
#include <ext/hash_map>
#include <base/Mutex.h>

namespace Shared
{

namespace Utility
{
///////////////////////////////////////////////
//	@brief	管理集合：用于对象管理。
//			线程安全, 不可重入，重入会造成死锁
///////////////////////////////////////////////

template<class Key,class Value>
class ObjectMgr
{
public:
	ObjectMgr();
	virtual ~ObjectMgr();
public:
	// Typdef
	typedef std::tr1::shared_ptr<Value> value_sptr;
	typedef typename __gnu_cxx::hash_map<Key,value_sptr>::iterator Iterator;
public:
	// 向管理集合中添加一个对象
	bool Append(Key k,Value * v)
	{
		MutexLockGuard lock(&m_mutex);
		
		value_sptr val(v);
		Iterator itr = m_objmap.find(k);	
		
		if(itr != m_objmap.end())
			return false;	
		else
		{
			m_objmap.insert(make_pair(k,val));	
		}
		return true;
	}
	
	// 从管理集合中获取一个对象
	bool Get(Key k,value_sptr& sptr)
	{
		MutexLockGuard lock(&m_mutex);
		
		Iterator itr = m_objmap.find(k);
		
		if(itr != m_objmap.end())
		{
			sptr = itr->second;
			return true;
		}

		return false;
	}

	// 从管理集合中取出一个对象
	bool Fetch(Key k, value_sptr& sptr)
	{
		MutexLockGuard lock(&m_mutex);
		
		Iterator itr = m_objmap.find(k);

		if(itr == m_objmap.end())
			return false;
		
		sptr = itr->second;
		m_objmap.erase(itr);	
		
		return true;
	}

	// 将对象从管理集合中移除
	bool Remove(Key k)
	{
		MutexLockGuard lock(&m_mutex);
		
		Iterator itr = m_objmap.find(k);
		
		if(itr == m_objmap.end())
			return false;
		
		itr->second.reset();
		m_objmap.erase(itr);
		
		return true;
	}

	// 清除所有对象
	void Clear()
	{
		MutexLockGuard lock(&m_mutex);
		Iterator itr;
		for(itr = m_objmap.begin(); itr != m_objmap.end(); )
		{
			itr->second.reset();
			m_objmap.erase(itr++);
		}
	}
private:
	mutable Mutex m_mutex;	// 锁
	__gnu_cxx::hash_map<Key,value_sptr> m_objmap;
};

}// END NAMESPACE UTILITY

}// END NAMESPACE SHARED
#endif
