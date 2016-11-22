/*
 * Copyright (c) 2012-2016 soymuchacho <guqi_282@126.com>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * > LIBSHARED  VERSION 		:		0.0.1 
 * > File Name					:		ObjectMgr.hpp
 * > Author						:		soymuchacho
 * > Created Time				:		2015-10
 * > brief						:		
 *
 * */

#ifndef UTILITY_OBJECT_MGR_H
#define UTILITY_OBJECT_MGR_H

#include <tr1/memory>
#include <ext/hash_map>
#include <base/Mutex.h>
#include <network/MemoryPool.h>
#include <functional>

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
	ObjectMgr(){
	
	}
	virtual ~ObjectMgr(){
		Clear();	
	}
public:
	// Typdef
	typedef std::tr1::shared_ptr<Value> value_sptr;
	typedef typename __gnu_cxx::hash_map<Key,value_sptr>::iterator Iterator;
public:
	unsigned int Count() {
		return m_objmap.size();
	}
public:
	/**
	 *	@brief 向集合中添加一个对象。
	 *
	 *	@param k	[in] 关键字
	 *	@param val	[in] 对象指针，该指针必须是由
	 *					 系统堆分配的内存。如果是
	 *					 本库的内存池分配，请使用
	 *					 楼下函数。
	 *	@param isUseSP [in] 是否使用了libshared库的内存池（memorypool）
	 *						默认为不使用，如若使用，请设置为true。
	 *
	 *	@return true	添加成功
	 *			false	添加失败
	 *
	 **/
	bool Append(Key k,Value * v,bool isUseMP = false)
	{
		MutexLockGuard lock(&m_mutex);

		value_sptr val;
	
		// 返回失败
		if(isUseMP)
			val.reset(v,SHARED_DELETE<Value>());
		else
			val.reset(v);
		
		Iterator itr = m_objmap.find(k);	
		
		if(itr != m_objmap.end())
			return false;	
		else
		{
			m_objmap.insert(make_pair(k,val));	
		}
		return true;
	}

	bool Append(Key k, value_sptr& sptr)
	{
		Iterator itr = m_objmap.find(k);
		if(itr != m_objmap.end())
			return false;
		else
			m_objmap.insert(make_pair(k,sptr));
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
public:
	/**< @brief 遍历，传入回调函数 >*/
	void Travalcall(std::function<bool (Key,value_sptr)> callback)
	{
		MutexLockGuard lock(&m_mutex);
		Iterator itr;
		for(itr = m_objmap.begin(); itr != m_objmap.end(); itr++)
		{
			if(callback(itr->first,itr->second))
				continue;
			else
				return ;
		}
	}
	
	template<class P1>
	void Travalcall(std::function<bool (Key,value_sptr,P1)> callback,P1 p1)
	{
		MutexLockGuard lock(&m_mutex);	
		Iterator itr;
		for(itr = m_objmap.begin(); itr != m_objmap.end(); itr++)
		{
			if(callback(itr->first,itr->second,p1))
				continue;
			else
				return ;
		}
	}

	template<class P1,class P2>
	void Travalcall(std::function<bool (Key,value_sptr,P1,P2)> callback,P1 p1,P2 p2)
	{
		MutexLockGuard lock(&m_mutex);	
		Iterator itr;
		for(itr = m_objmap.begin(); itr != m_objmap.end(); itr++)
		{
			if(callback(itr->first,itr->second,p1,p2))
				continue;
			else
				return ;
		}
	}


	template<class P1,class P2,class P3>
	void Travalcall(std::function<bool (Key,value_sptr,P1,P2,P3)> callback,P1 p1, P2 p2,P3 p3)
	{
		MutexLockGuard lock(&m_mutex);	
		Iterator itr;
		for(itr = m_objmap.begin(); itr != m_objmap.end(); itr++)
		{
			if(callback(itr->first,itr->second,p1,p2,p3))
				continue;
			else
				return ;
		}
	}
private:
	mutable Mutex m_mutex;	// 锁
	// hash map使用key和智能指针
	__gnu_cxx::hash_map<Key,value_sptr> m_objmap;
};

}// END NAMESPACE UTILITY

}// END NAMESPACE SHARED
#endif
