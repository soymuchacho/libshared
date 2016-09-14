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
 * > File Name					:		time-task.cpp
 * > Author						:		soymuchacho
 * > Created Time				:		2016年09月14日 星期三 09时54分10秒
 * > brief						:		
 *
 * */

#include <Event_Interface.h>
#include <network/Epoll_Engine.h>
#include <base/Log.h>


void * TimerCallBack(int fd, int arg, void * args)
{
	LOG2("R","release","this is timer callback : %d %d ",fd,arg);
}

int main()
{
	// 初始化日志
	Shared::Shared_Log().Initialize("time_output",Shared::LOG_RELEASE);
	
	// 初始化引擎 
	Shared::sockengine_sptr engine;
	Shared::Init_Engine<Shared::Epoll_Engine>(engine);

	// 加入时间事件
	Shared::Event * ev = NULL;
	shared_registertimerevent(engine,ev,TimerCallBack,10,20,NULL,1000);

	engine->Engine_Loop();
	// 销毁事件ev
	Shared::RemoveEvent(engine,ev);
	return 0;
}




