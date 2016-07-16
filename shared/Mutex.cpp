/**
 *	> Copyright(c) 2015 guqi
 *
 *	> LIBSHARED  VERSION :		0.0.1 
 *
 *	> File Name			 :		Mutex.cpp
 *
 *	> Author			 :		guqi
 *
 *	> Mail				 :		guqi_282@126.com
 *
 *	> Created Time		 :		2015-10
 *
 * */

#include <base/Mutex.h>
#include <base/Log.h>

namespace Shared
{

Mutex::Mutex()
{
	pthread_mutex_init(&m_mutex,NULL);
}

Mutex::~Mutex()
{
	pthread_mutex_destroy(&m_mutex);
}

void Mutex::Lock()
{
	pthread_mutex_lock(&m_mutex);
}

void Mutex::UnLock()
{
	pthread_mutex_unlock(&m_mutex);
}

void Mutex::Acquire()
{
	Lock();
}

void Mutex::Release()
{
	UnLock();
}

bool Mutex::AttemptAcquire()
{
	if(!pthread_mutex_trylock(&m_mutex))
		return true;
	else 
		return false;
}

}
