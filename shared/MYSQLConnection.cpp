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
 * > File Name					:		MYSQLConnection.cpp
 * > Author						:		soymuchacho
 * > Created Time				:		2016年09月22日 星期四 09时54分16秒
 * > brief						:		
 *
 * */

#include <sql/MYSQLConnection.h>
#include <network/MemoryPool.h>
#include <base/Log.h>

namespace Shared
{

namespace SQL
{

MYSQLConnection::MYSQLConnection()
{
	m_sqlsock = NULL;
	m_retset = NULL;
	memset(m_host,0,MYSQL_HOST_SIZE);
	memset(m_user,0,MYSQL_USER_SIZE);
	memset(m_pwd,0,MYSQL_PWD_SIZE);
	memset(m_db,0,MYSQL_DB_SIZE);
}

MYSQLConnection::~MYSQLConnection()
{
	mysql_close(m_sqlsock);
}

bool MYSQLConnection::ConnectMYSQL(char * host,char * user,char * pwd,char * db)
{
	if(host == NULL || user == NULL || pwd == NULL || db == NULL)
	{
		return false;
	}
	// 赋值给成员变量
	strncpy(m_host,host,MYSQL_HOST_SIZE - 1);
	strncpy(m_user,user,MYSQL_USER_SIZE - 1);
	strncpy(m_pwd,pwd,MYSQL_PWD_SIZE - 1);
	strncpy(m_db,db,MYSQL_DB_SIZE - 1);
	// 初始化
	if( !(m_sqlsock = mysql_init(0)) )
	{
		LOGDEBUG("mysql","mysql init error!");
		return false;
	}
	unsigned long flag;
	// 连接数据库
	if( !mysql_real_connect(m_sqlsock,m_host,m_user,m_pwd,m_db,3306,NULL,flag))
	{
		LOGDEBUG("mysql","errno(%d) : %s",mysql_errno(m_sqlsock),mysql_error(m_sqlsock));
		return false;
	}
	return true;
}

bool MYSQLConnection::ReconnectMYSQL()
{
	// 关闭原先连接
	mysql_close(m_sqlsock);

	return true;
}

bool MYSQLConnection::RealQuery(string sql)
{
	int ret = mysql_real_query(m_sqlsock,sql.c_str(),sql.length());
	if(ret != 0)
	{
		return false;
	}
	
	firstFetch = true;
	
	return true;
}

ResultSet * MYSQLConnection::FetchResultSet()
{
	ResultSet * res = NULL;

	if(firstFetch)
	{
		// 第一此获取
		ResultSet * res = MM_NEW<ResultSet>();
		if(res == NULL)
		{
			LOGDEBUG("mysql","malloc error");
			return NULL;
		}
		res->Initialize(m_sqlsock);
		firstFetch = false;
	}
	else
	{
		// 获取后面的结果集合
		if(mysql_next_result(m_sqlsock) == 0)
		{
			ResultSet * res = MM_NEW<ResultSet>();
			if(res == NULL)
			{
				LOGDEBUG("mysql","malloc error");
				return NULL;
			}
			res->Initialize(m_sqlsock);
		}
	}
	return res;
}

void MYSQLConnection::Update()
{
	if(mysql_ping(m_sqlsock) != 0)
	{
		ReconnectMYSQL();
	}
}

}//END NAMESPACE MYSQL

}//END NAMESPACE SHARED

