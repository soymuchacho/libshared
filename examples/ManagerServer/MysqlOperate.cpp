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
 * > File Name					:		MysqlOperate.cpp
 * > Author						:		soymuchacho
 * > Created Time				:		2017年03月03日 星期五 15时50分46秒
 * > brief						:		
 *
 * */

#include "MysqlOperate.h"

initializeSingleton(MysqlOperate);


MysqlOperate::MysqlOperate()
{

}

MysqlOperate::~MysqlOperate()
{

}

bool MysqlOperate::Initialize()
{
    // 读取配置文件...获取host,db,user,pwd
    SharedConfig.Initialize("cfg_mysqldb.ini");
    char host[256] = {0};
    char user[64] = {0};
    char pwd[64] = {0};
    char db[64] = {0};

    SharedConfig.GetStringValue("db_host",host,256);
    SharedConfig.GetStringValue("db_user",user,64);
    SharedConfig.GetStringValue("db_pwd",pwd,64);
    SharedConfig.GetStringValue("db_database",db,64);

    OUTPUT("mysql","connect mysql : host[%s] db[%s] user[%s] pwd[%s]",host,db,user,pwd);
    if( ConnectDB(host,user,pwd,db) == false )
    {
        OUTPUT("mysql","mysql connect failed!");
        return false;
    }
    OUTPUT("mysql","mysql connect successful!");
    
    // 创建时间事件
    Shared::sockengine_sptr engine = Shared::GetGlobalCurrentEngine();
    if(engine)
    {
        OUTPUT("mysql","mysql update timer event create");
        shared_registertimerevent(engine,m_update,MysqlOperate::UpdateTimeEventCallBack,0,0,NULL,1000);
    }
    return true;
}

void * MysqlOperate::UpdateTimeEventCallBack(int f, int arg,void * args)
{
    OUTPUT("mysql","update");
    sMysqlOpMgr.Update();
    return 0;
}

