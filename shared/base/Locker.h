/**
 *	> Copyright(c) 2015 guqi
 *
 *	> LIBSHARED  VERSION :		0.0.1 
 *
 *	> File Name			 :		Locker.h
 *
 *	> Author			 :		guqi
 *
 *	> Mail				 :		guqi_282@126.com
 *
 *	> Created Time		 :		2015-10
 *
 * */

#ifndef SHARED_LOCKER_H
#define SHARED_LOCKER_H

#include <semaphore.h>
#include <pthread.h>
#include <include/Common.h>

namespace Shared
{
/*
 *
 * @brief 信号量，条件变量
 *
 */
class Sem
{
public:
	Sem();
	~Sem();
public:
	bool Wait();
	bool Post();
protected:
	sem_t m_sem;
};

class Cond
{
public:
	Cond();
	~Cond();
public:
	bool Wait();
	// 唤醒等待的条件变量
	bool Signal();
protected:
	pthread_mutex_t m_mutex;
	pthread_cond_t	m_cond;
};

}// END NAMESPACE

#endif// END SHARED_LOCKER_H
