/**
 *	> Copyright(c) 2015 guqi
 *
 *	> LIBSHARED  VERSION :		0.0.1 
 *
 *	> File Name			 :		Mutex.h
 *
 *	> Author			 :		guqi
 *
 *	> Mail				 :		guqi_282@126.com
 *
 *	> Created Time		 :		2015-10
 *
 * */

#ifndef SHARED_MUTEX_H
#define SHARED_MUTEX_H

#include <base/NonCopyable.h>
#include <include/Common.h>

namespace Shared
{

class Mutex
{
public:
	Mutex();
	~Mutex();
public:
	void Lock();
	void UnLock();
	bool AttemptAcquire();
	void Acquire();
	void Release();
protected:
	pthread_mutex_t m_mutex;
};

// RAII.....
class MutexLockGuard
{
public:
	MutexLockGuard(Mutex*  mutex)
		:m_mutex(mutex)
	{
		m_mutex->Lock();
	}

	~MutexLockGuard()
	{
		m_mutex->UnLock();
	}
	Mutex *m_mutex;
};

}// END NAMESPACE
#endif// END SHARED_MUTEX_H
