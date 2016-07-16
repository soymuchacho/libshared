/**
 *	> Copyright(c) 2015 guqi
 *
 *	> LIBSHARED  VERSION :		0.0.1 
 *
 *	> File Name			 :		mm_Task.h
 *
 *	> Author			 :		guqi
 *
 *	> Mail				 :		guqi_282@126.com
 *
 *	> Created Time		 :		2015-10
 *
 * */

#ifndef SHARED_MM_TASK_H
#define SHARED_MM_TASK_H

#include <network/BaseTask.h>

namespace Shared
{

enum SWITCH_MM_TASK
{
	SWITCH_MM_TASK_ONWRITE = 1,
	SWITCH_MM_TASK_ONREAD,
	SWITCH_MM_TASK_ONERROR,
};

class MM_Task : public BaseTask
{
public:
	MM_Task(SWITCH_MM_TASK swi,Socket_Engine * se,unsigned int fd,unsigned long ctime);
	virtual ~MM_Task();
public:
	SWITCH_MM_TASK GetTaskSwitch()	{	return m_taskSwi;	}
	bool GetSocket(basesocket_sptr &);	
	Socket_Engine * GetSocketEngine()	{	return m_se;	}
protected:
	SWITCH_MM_TASK m_taskSwi;
	Socket_Engine * m_se;
	// fd 和 ctime 找到要处理的socket，实时寻找，
	// 避免直接传进socket，偶尔socket释放，而导致
	// 错误的指针，引起程序崩溃
	unsigned int	m_fd;
	unsigned long	m_ctime;
};
}
#endif

