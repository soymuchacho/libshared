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
 * > File Name					:		MYSQLConnection.h
 * > Author						:		soymuchacho
 * > Created Time				:		2016年09月22日 星期四 09时54分06秒
 * > brief						:		
 *
 * */


#ifndef SHARED_MYSQL_CONNECTION_H
#define SHARED_MYSQL_CONNECTION_H

#include <base/NonCopyable.h>
#include <mysql.h>

namespace Shared
{

namespace MYSQL
{

// 数据库状体
typedef enum mysql_connection_state
{
	MYSQL_CONNECTION_BUSY,
	MYSQL_CONNECTION_IDLE,
}MYSQL_CONNECTION_STATE;

#define MYSQL_HOST_SIZE		64
#define MYSQL_USER_SIZE		MYSQL_HOST_SIZE
#define MYSQL_PWD_SIZE		MYSQL_HOST_SIZE
#define MYSQL_DB_SIZE		MYSQL_HOST_SIZE

// 数据库连接类
class MYSQLConnection : public noncopyable
{
public:
	MYSQLConnection();
	~MYSQLConnection();
public:
	/**
	 *	@brief 连接数据库
	 *
	 **/
	bool ConnectMYSQL(char * host,char * user,char * pwd,char * db);
	/**
	 *	@brief 数据库重新连接
	 */
	bool ReconnectMYSQL();
	/*
	 *	@brief 执行sql语句
	 */
	bool RealQuery(string sql);
	/**
	 *	@brief 获取一个结果集
	 */
	ResultSet * FetchResultSet();
	/**
	 *	@brief 检测数据库连接状态，如果连接断开，则进行重连
	 */
	void Update();
private:
	MYSQL *		m_sqlsock;				/**< mysql连接句柄 >*/
	ResultSet * m_retset;				/**< 数据库结果集 >*/
	bool		firstFetch;				/**< 第一次获取结果集 >*/
private:
	char		m_host[MYSQL_HOST_SIZE];				/**< 数据库host >*/
	char		m_user[MYSQL_USER_SIZE];				/**< 数据库用户名 >*/
	char		m_pwd[MYSQL_PWD_SIZE];				/**< 数据库用户的密码 >*/
	char		m_db[MYSQL_DB_SIZE];				/**< 需要连接的数据库 >*/
};//END CLASS MYSQLCONNECTION

}//END NAMESPACE MYSQL

}//END NAMESPACE SHARED

#endif
