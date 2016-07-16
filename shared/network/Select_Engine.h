/**
 *	> Copyright(c) 2015 guqi
 *
 *	> LIBSHARED  VERSION :		0.0.1 
 *
 *	> File Name			 :		Select_Engine.h
 *
 *	> Author			 :		guqi
 *
 *	> Mail				 :		guqi_282@126.com
 *
 *	> Created Time		 :		2015-10
 *
 * */

#ifndef SHARED_SELECT_ENGINE_H
#define SHARED_SELECT_ENGINE_H

#include <network/Socket_Engine.h>

namespace Shared
{

class Select_Engine : public Socket_Engine
{
public:
	Select_Engine();
	virtual ~Select_Engine();
public:
	bool AddSocket(BaseSocket *);
	void DeleteSocket(BaseSocket *);
	bool RemoveSocket(BaseSocket *);
	void WantRead(BaseSocket *);
	void WantWrite(BaseSocket *);
	void ShutDown();
	BaseSocket * GetSocket(int);
	BaseSocket * GetSocket(unsigned long ,unsigned long);
public:
	void Select_Loop();
protected:
	int m_fdread;
	int m_fdwrite;
	int m_fdexception;
	int m_maxfd;
	int FdNum;
};

}
#endif
