/**
 *	> Copyright(c) 2015 guqi
 *
 *	> LIBSHARED  VERSION :		0.0.1 
 *
 *	> File Name			 :		CMyTimer.h
 *
 *	> Author			 :		guqi
 *
 *	> Mail				 :		guqi_282@126.com
 *
 *	> Created Time		 :		2015-10
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
