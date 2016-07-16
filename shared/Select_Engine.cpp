/**
 *	> Copyright(c) 2015 guqi
 *
 *	> LIBSHARED  VERSION :		0.0.1 
 *
 *	> File Name			 :		Select_Engine.cpp
 *
 *	> Author			 :		guqi
 *
 *	> Mail				 :		guqi_282@126.com
 *
 *	> Created Time		 :		2015-10
 *
 * */

#include <network/Select_Engine.h>
#include <network/BaseSocket.h>

namespace Shared
{

Select_Engine::Select_Engine()
{
	FD_ZERO(&m_fdread);
	FD_ZERO(&m_fdwrite);
	FD_ZERO(&m_fdexception);
}

Select_Engine::~Select_Engine()
{

}

bool Select_Engine::AddSocket(BaseSocket * s)
{
	return true;
}

void Select_Engine::Select_Loop()
{

	if(select(m_maxfd,&m_fdread,&m_fdwrite,&m_fdexception,0))
	{
	
	}
}

}
