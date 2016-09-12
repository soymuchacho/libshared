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
 * > File Name					:		CMyTimer.h
 * > Author						:		soymuchacho
 * > Created Time				:		2015-10
 * > brief						:		时间 
 *
 * */

#ifndef SHARED_CMYTIMER_H
#define SHARED_CMYTIMER_H

namespace Shared
{

class CMyTimer  
{
private:
	uint32 m_uTickTerm;
	uint32 m_uTickOld;

public:
	bool m_bOper;

public: 
	CMyTimer()
	{
		CleanUp() ;
	}

	bool IsSetTimer( ){ return m_bOper ; }

	void SetTermTime( uint32 uTerm ){ m_uTickTerm =uTerm; }
	uint32 GetTermTime( ){ return m_uTickTerm ; }

	uint32 GetTickOldTime( ){ return m_uTickOld; }

	void CleanUp( )
	{ 
		m_uTickTerm = 0 ;
		m_bOper = false ;
		m_uTickOld = 0 ;
	}

	void BeginTimer(uint32 uTerm, uint32 uNow)
	{
		m_bOper = true;
		m_uTickTerm =uTerm;     
		m_uTickOld =uNow;
	}

	bool CountingTimer(uint32 uNow)
	{
		if(!m_bOper)
			return false;

		uint32 uNew =uNow;

		if(uNew<m_uTickOld+m_uTickTerm )
			return false;

		m_uTickOld =uNew;

		return true;
	}
	uint32 GetLeaveTime(uint32 uNow)//剩余时间;
	{
		if(!CountingTimer(uNow))
		{
			return m_uTickTerm+m_uTickOld-uNow;
		}
		return 0;
	}
	uint32	GetPassTime(uint32 uNow)
	{
		return uNow - m_uTickOld;
	}	
};

}// END NAMESPACE

#endif// END SHARED_CMYTIMER_H
