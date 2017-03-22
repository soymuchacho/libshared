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
 * > File Name					:		main.cpp
 * > Author						:		soymuchacho
 * > Created Time				:		2017年03月03日 星期五 16时48分25秒
 * > brief						:		
 *
 * */

#include <iostream>
#include <include/Shared.h>
#include "LoginSocket.h"
using namespace std;
using namespace Shared;

int main()
{
    // 初始化配置文件
    SharedConfig.Initialize("./cfg_server.ini");
    // 初始化日志
    SharedLog.Initialize("output.log",LOG_DEBUG);
    // 初始化epoll engine
    sockengine_sptr epoll_engine;
    Init_Engine<Epoll_Engine>(epoll_engine);
    if(!epoll_engine)
    {
        OUTPUT("main","init epoll engine error!");
        return 0;
    }
    OUTPUT("main","init socket engine successful");
    // 获取ip,port配置
    char ip[256] = {0};
    short int port = 0;
    SharedConfig.GetStringValue("ip",ip,256);
    port = SharedConfig.GetIntValue("port");
    // 创建监听
    if( CreateListenSocket<LoginSocket>(epoll_engine,ip,port) == false )
    {
        OUTPUT("main","create listen socket error!ip = %s , port = %d ",ip,port);
        return 0;
    }
    OUTPUT("main","create listen socket successful!ip = %s, port = %d",ip,port);

    // 开启大循环
    epoll_engine->Engine_Loop();
    return 0;
}

