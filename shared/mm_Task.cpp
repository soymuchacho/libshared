/**
 *	> Copyright(c) 2015 guqi
 *
 *	> LIBSHARED  VERSION :		0.0.1 
 *
 *	> File Name			 :		mm_Task.cpp
 *
 *	> Author			 :		guqi
 *
 *	> Mail				 :		guqi_282@126.com
 *
 *	> Created Time		 :		2015-10
 *
 * */

#include <network/mm_Task.h>
#include <network/BaseSocket.h>
#include <network/Socket_Engine.h>

namespace Shared
{

MM_Task::MM_Task(SWITCH_MM_TASK swi,Socket_Engine * se,unsigned int fd,unsigned long ctime)
	: BaseTask(),
	 m_taskSwi(swi),
	 m_se(se),
	 m_fd(fd),
	 m_ctime(ctime)
{

}

MM_Task::~MM_Task()
{
}


bool MM_Task::GetSocket(basesocket_sptr & s)	
{	
	if(m_se != NULL)
	{
		return m_se->GetSocket(m_fd,m_ctime,s);
	}
	return false;
}

}
