/**
 *	> Copyright(c) 2015 guqi
 *
 *	> LIBSHARED  VERSION :		0.0.1 
 *
 *	> File Name			 :		test.cpp
 *
 *	> Author			 :		guqi
 *
 *	> Mail				 :		guqi_282@126.com
 *
 *	> Created Time		 :		2015-12
 *
 * */

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

class Mutex
{
public:
	Mutex()
	{
		pthread_mutex_init(&m_mutex,NULL);	
	}
	~Mutex()
	{
		pthread_mutex_destory(&m_mutex);	
	}
	void Lock()
	{
		pthread_mutex_lock(&m_mutex);
	}
	void UnLock()
	{
		pthread_mutex_unlock(&m_mutex);
	}

	pthread_mutex_t m_mutex;
};

class MutexLockGuard
{
public:
	MutexLockGuard(Mutex & mutex)
		: m_mutex(mutex)
	{
		mutex.Lock();
	}
	MutexLockGuard(pthread)
};

void Malloc()
{
	pthread_mutex_lock(&m_mutex);
	printf("++++++++++++++++++开始使用\n");
	printf("------------------使用结束\n");
	pthread_mutex_unlock(&m_mutex);
}

void Free()
{
	pthread_mutex_lock(&m_mutex);
	printf("++++++++++++++++++开始使用\n");
	printf("------------------使用结束\n");
	pthread_mutex_unlock(&m_mutex);
}

static void * work(void *arg)
{
	pthread_detach(pthread_self());
	for(int i = 0; i < 10000;i++)
	{
		Malloc();	
		Free();
	}
	return NULL;
}

int main()
{
	for(int i = 0; i < 50; i++)
	{
		pthread_t tid = 0;
		if(pthread_create(&tid,NULL,work,NULL) != 0)
		{
			printf("pthread create error!\n");
			return 0;
		}
		usleep(10);
	}
	while(1);
	return 0;
}

