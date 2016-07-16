/**
 *	> Copyright(c) 2015 guqi
 *
 *	> LIBSHARED  VERSION :		0.0.1 
 *
 *	> File Name			 :		BaseTask.h
 *
 *	> Author			 :		guqi
 *
 *	> Mail				 :		guqi_282@126.com
 *
 *	> Created Time		 :		2015-10
 *
 * */

#ifndef SHAERD_BASE_TASK_H
#define SHAERD_BASE_TASK_H

#include <network/Socket_Engine.h>

namespace Shared
{

class BaseTask
{
public:
	BaseTask()	{}
	virtual ~BaseTask()	{}
public:
	virtual bool GetSocket(basesocket_sptr &) = 0;
protected:
	void * param;
};

}
#endif
