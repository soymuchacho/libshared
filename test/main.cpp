/**
*	> File Name: main.cpp
*	> Author: guqi
*	> Mail: guqi_282@126.com
*	> Created Time: 2015年11月23日 星期一 11时11分23秒
 **/

#include <base/Log.h>
#include <network/Epoll_Engine.h>
#include <network/TimerEvent.h>
#include <Event_Interface.h>
#include <signal.h>
#include <pthread.h>

struct data
{
	int a;
	int b;
	void * c;
};

static void * work(void * arg);
int main()
{
	for(int i = 0; i < 50; i++)
	{
		printf("创建第%d个线程\n",i+1);
		pthread_t tid = 0;
		if(pthread_create(&tid,NULL,work,NULL) != 0)
		{
			printf("create pthread error");
			return 0;
		}
	}
	while(true);
	return 0;
}

static void * work(void * arg)
{
	pthread_detach(pthread_self());

	for(int i = 0; i < 50000; i++)
	{
		data * da = Shared::MM_NEW<data>();
		usleep(20);
		Shared::MM_DELETE(da);
		usleep(10);
	}

	return NULL;
}
