/**
 *	> Copyright(c) 2015 guqi
 *
 *	> LIBSHARED  VERSION :		0.0.1 
 *
 *	> File Name			 :		Locker.cpp
 *
 *	> Author			 :		guqi
 *
 *	> Mail				 :		guqi_282@126.com
 *
 *	> Created Time		 :		2015-10
 *
 * */

#include <base/Locker.h>

namespace Shared
{

Sem::Sem()
{
	int ret = 0;
	ret = sem_init(&m_sem,0,0);
	ASSERT(ret != 0);
}

Sem::~Sem()
{
	sem_destroy(&m_sem);
}

bool Sem::Wait()
{
	return sem_wait(&m_sem) == 0;
}

bool Sem::Post()
{
	return sem_post(&m_sem) == 0;
}

// 华丽的分割线 
///////////////////////////////////////////////////////////////////////////////

Cond::Cond()
{
	int ret = 0;
	ret = pthread_mutex_init(&m_mutex,NULL);
	ASSERT(ret != 0);

	ret = pthread_cond_init(&m_cond,NULL);
	ASSERT(ret != 0);
}

Cond::~Cond()
{
	pthread_mutex_destroy(&m_mutex);
	pthread_cond_destroy(&m_cond);
}

bool Cond::Wait()
{
	int ret = 0;
	pthread_mutex_lock(&m_mutex);
	ret = pthread_cond_wait(&m_cond,&m_mutex) == 0;
	return ret == 0;
}


bool Cond::Signal()
{
	return pthread_cond_signal(&m_cond) == 0;
}


}
