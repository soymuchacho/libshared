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
 * > File Name					:		Mail.cpp
 * > Author						:		soymuchacho
 * > Created Time				:		2017年03月03日 星期五 15时59分35秒
 * > brief						:		
 *
 * */

#include "Mail.h"
#include <common/MemoryPool.h>
#include <common/Log.h>

Mail::Mail(char * smtp,char * mail, char * mailpwd)
    :m_sock(0),
     m_fd(0),
     m_port(25),
     m_IsConnected(false)
{
    if(smtp)
        strncpy(m_smtp,smtp,MAIL_ARRARY_SIZE);
    else
        memset(m_smtp,0,MAIL_ARRARY_SIZE);

    if(mail)
        strncpy(m_mail,mail,MAIL_ARRARY_SIZE);
    else
        memset(m_mail,0,MAIL_ARRARY_SIZE);

    if(mailpwd)
        strncpy(m_mailpwd,mailpwd,MAIL_ARRARY_SIZE);
    else
        memset(m_mailpwd,0,MAIL_ARRARY_SIZE);
}

Mail::~Mail()
{

}

bool Mail::SendEmail(char * email,char * content)
{
    LOG2("ManagerServer","Mail","开始连接SMTP服务器[%s]..",m_smtp);
    m_sock = socket(AF_INET,SOCK_STREAM,0);
    if(m_sock < 0)
    {
        LOG2("ManagerServer","Mail","连接SMTP服务器[%s]失败：创建socket失败！",m_smtp);
        return false;
    }
    struct sockaddr_in ser;
    ser.sin_family = AF_INET;
    ser.sin_port = htons(m_port);

    hostent * ht = gethostbyname(m_smtp);
    if(ht == NULL)
    {
        LOG2("ManagerServer","Mail","连接SMTP服务器[%s]失败: 获取smtp服务器ip地址出错！",m_smtp);
        return false;
    }

    memcpy(&ser.sin_addr.s_addr,ht->h_addr_list[0],ht->h_length);

    if( (m_fd = connect(m_sock,(struct sockaddr *)&ser,sizeof(ser))) < 0)
    {
        LOG2("ManagerServer","Mail","连接SMTP服务器[%s]失败: 连接smtp服务器出错！",m_smtp);
        return false;
    }
    LOG2("ManagerServer","Mail","连接SMTP服务器[%s]成功",m_smtp);
    return true;
}

void Mail::Close()
{

}




