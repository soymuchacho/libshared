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
 * > File Name					:		mm_Task.h	
 * > Author						:		soymuchacho
 * > Created Time				:		2015-10
 * > brief						:		
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

