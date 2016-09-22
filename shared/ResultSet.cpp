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
 * > File Name					:		ResultSet.cpp
 * > Author						:		soymuchacho
 * > Created Time				:		2016年09月22日 星期四 10时23分53秒
 * > brief						:		
 *
 * */

#include <mysql/ResultSet.h>

namespace Shared
{

namespace MYSQL
{

ResultSet::ResultSet()
{
	
}

ResultSet::~ResultSet()
{
	mysql_free_result(m_result);
}

bool ResultSet::Initialize(MYSQL * sock)
{
	m_sqlsock = sock;
	m_result = mysql_store_result(sock);
	
	if(m_result == NULL)
	{
		LOGDEBUG("mysql","mysql_store_result return null!");
		return false;
	}

	return true;;
}

unsigned long ResultSet::GetString(unsigned int row, unsigned int field,char ** value)
{
	if(m_row != row)
	{
		m_mysqlrows = mysql_fetch_row(result);
		m_lengths = mysql_fetch_lengths(result); 
		this->row = row;
	}
	
	*value = m_mysqlrows[field];
	return m_legths[field];
}

unsigned int ResultSet::FieldCount()
{
	return mysql_field_count(m_sqlsock);
}

unsigned int ResultSet::RowCount()
{
	return mysql_affected_rows(m_sqlsock);
}

}//END NAMESPACE MYSQL

}//END NAMESPACE SHARED

