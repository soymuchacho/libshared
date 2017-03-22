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
 * > File Name					:		TimeSocket.cpp
 * > Author						:		soymuchacho
 * > Created Time				:		2016年09月14日 星期三 10时50分21秒
 * > brief						:		
 *
 * */

#include "TimeSocket.h"
#include <utility/TimeManager.h>
#include <include/Shared.h>
std::once_flag TimeSocket::m_flag;

TimeSocket::TimeSocket()
{
    std::call_once(m_flag,LoadHandles);
}

TimeSocket::TimeSocket(int fd, const struct sockaddr_in * peer)
	: TcpSocket(fd,peer)
{
    std::call_once(m_flag,LoadHandles);
}

TimeSocket::~TimeSocket()
{

}

void TimeSocket::LoadHandles()
{
    Shared::sockengine_sptr engine = Shared::GetGlobalCurrentEngine();
	if(engine)
	{
		LOG2("server","daytime","register io event eid %d",MSG_GET_DAY_TIME);
		shared_registerioevent(engine,MSG_GET_DAY_TIME,
				TimeSocket::HandleGetDayTime);
	}

}

void TimeSocket::OnConnect()
{
	LOG("server","daytime","fd",this->GetFd(),"---新用户连接---");
}

void TimeSocket::OnDisConnect()
{
	LOG("server","daytime","fd",this->GetFd(),"---连接关闭---");
}

bool TimeSocket::Dispatch()
{
	LOG2("server","daytime","Dispatch()!!!!");

	int rdsize = 0;
	memset(&m_head,0,sizeof(MSG_HEAD));
	if((rdsize = readBuffer->Read((char *)&m_head,sizeof(MSG_HEAD))) == sizeof(MSG_HEAD))
	{
		m_dlen = m_head.packsize;
		
		m_data = (char *)Shared::MM_MALLOC(m_dlen);
		if(m_data == NULL)
		{
			LOG2("server","daytime","malloc error!");
			return false;
		}

		if((rdsize = readBuffer->Read(m_data,m_dlen)) == m_dlen)
		{
			bool ret = HandleMessage();
			Shared::MM_FREE(m_data);
			return ret;
		}
		LOG2("server","daytime","read package error!rdsize %d m_dlen %d",rdsize,m_dlen);
		Shared::MM_FREE(m_data);
		return false;
	}
	LOG2("server","daytime","read data error!rdsize %d",rdsize);
	return false;
}

bool TimeSocket::HandleMessage()
{
	Shared::sockengine_sptr engine;
	if(GetSocketEngine(engine))
	{
		LOG2("server","daytime","find this eid %d",m_head.eid);
		return engine->Event_IO_Excute(m_head.eid,this->GetFd(),m_dlen,m_data);
	}
	LOG2("server","daytime","can't find this eid %d",m_head.eid);
	return true;
}

void * TimeSocket::HandleGetDayTime(int fd, int size , void * data)
{
    Shared::sockengine_sptr engine = Shared::GetGlobalCurrentEngine();
	if(!engine)
    {
        LOG2("server","daytime","can't find engine!");
        return NULL;
    }
    
    Shared::basesocket_sptr basesock;
    engine->GetSocket(fd,basesock);
    if(!basesock)
    {
        LOG2("server","daytime","can't find socket instance!");
        return NULL;
    }
    
    timesocket_sptr tsp = dynamic_pointer_cast<TimeSocket>(basesock);
    if(!tsp)
    {
        LOG2("server","daytime","can't find socket instance!");
        return NULL;
    }

    LOG2("server","daytime","recv get day time msg");
	unsigned int now_time = time(NULL); 
	struct tm * now_tm;
	now_tm = localtime((time_t *)&now_time);

	CMSG_GET_DAY_TIME daytime;
	memset(&daytime,0,sizeof(CMSG_GET_DAY_TIME));
	sprintf(daytime.daytime,"%d-%d-%d %d:%d:%d",now_tm->tm_year + 1900,
			now_tm->tm_mon + 1,now_tm->tm_mday,now_tm->tm_hour,now_tm->tm_min,now_tm->tm_sec);	
    
    MSG_HEAD head;
    head.eid = MSG_GET_DAY_TIME;
    head.packsize = sizeof(CMSG_GET_DAY_TIME);
    // 发送包头
	tsp->Write(&head,sizeof(MSG_HEAD));
	// 发送数据包
	tsp->Write(&daytime,sizeof(CMSG_GET_DAY_TIME));
}
