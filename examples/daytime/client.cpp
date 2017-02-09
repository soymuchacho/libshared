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
 * > File Name					:		client.cpp
 * > Author						:		soymuchacho
 * > Created Time				:		2016年09月14日 星期三 11时53分07秒
 * > brief						:		
 *
 * */

#include "Protocol.h"
#include <include/Event_Interface.h>
#include <common/Config.h>
#include <include/Event.h>

class ClientSocket : public Shared::TcpSocket
{
public:
	ClientSocket(){
	
	}

	ClientSocket(int fd, const struct sockaddr_in * peer)
		:TcpSocket(fd,peer)
	{
	
	}

	virtual ~ClientSocket()
	{
	
	}
public:
	void * CheckTimer(int fd, int arg, void * args)
	{
		int allsize = sizeof(MSG_HEAD) + sizeof(CMSG_GET_DAY_TIME);
		char * buffer = (char *)Shared::MM_MALLOC(allsize);

		if(buffer == NULL)
			return NULL;
		memset(buffer,0,allsize);

		MSG_HEAD * head = (MSG_HEAD *)buffer;
		// 发送包头
		head->eid = MSG_GET_DAY_TIME;
		head->packsize = sizeof(CMSG_GET_DAY_TIME);

		LOG2("client","daytime","send pack eid %d size %d",head->eid,head->packsize);
		Write(buffer,allsize);
		return NULL;
	}
public:
	virtual bool Dispatch()
	{
		int rdsize = 0;
		memset(&m_head,0,sizeof(MSG_HEAD));
		if((rdsize = readBuffer->Read((char *)&m_head,sizeof(MSG_HEAD))) == sizeof(MSG_HEAD))
		{
			m_dlen = m_head.packsize;
			m_data = (char *)Shared::MM_MALLOC(m_dlen);
			if(m_data == NULL)
				return false;

			if((rdsize = readBuffer->Read(m_data,m_dlen)) == m_dlen)
			{
				CMSG_GET_DAY_TIME * daytime = (CMSG_GET_DAY_TIME *)m_data;
				LOG2("client","daytime","当前服务器的时间 ： %s",daytime->daytime);
				Shared::MM_FREE(m_data);
				return true;
			}
			Shared::MM_FREE(m_data);
		}
		return true;
	}

	virtual void OnConnect()
	{
		LOG2("client","daytime","连接上服务器");
		
		Shared::sockengine_sptr engine;
		if(GetSocketEngine(engine))
		{
			shared_registertimerevent(engine,m_ev,std::bind(&ClientSocket::CheckTimer,this,
						std::placeholders::_1,
						std::placeholders::_2,
						std::placeholders::_3),0,0,NULL,2000);
		}

	}

	virtual void OnDisConnect()
	{
		LOG2("client","daytime","与服务器断开连接");
		Shared::sockengine_sptr engine;
		if(GetSocketEngine(engine))
		{
			Shared::RemoveEvent(engine,m_ev);
		}
	}
private:
	MSG_HEAD		m_head;
	char *			m_data;
	int				m_dlen;
	Shared::Event * m_ev;
};

int main()
{
	// 初始化日志
	Shared::Shared_Log().Initialize("client_output",Shared::LOG_RELEASE);

	// 初始化配置文件
	Shared::Shared_Config().Initialize("cfg_daytime.ini");

	// 初始化引擎
	Shared::sockengine_sptr engine;
	Shared::Init_Engine<Shared::Epoll_Engine>(engine);

	// 从配置文件中获取ip和port
	char szIp[64] = {0};
	Shared::Shared_Config().GetStringValue("ip",szIp,64);
	int port = Shared::Shared_Config().GetIntValue("port");

	Shared::basesocket_sptr sock;
	// 连接服务器
	bool ret = Shared::ConnectTCPSocket<ClientSocket>(engine,szIp,port,sock);
	if(!ret)
	{
		LOG2("client","daytime","connect ip %s port %d error!",szIp,port);
		return 0;
	}
	LOG2("client","daytime","connect ip %s port %d successful",szIp,port);

	engine->Engine_Loop();

	Shared::Shutdown_Engine(engine);
}

