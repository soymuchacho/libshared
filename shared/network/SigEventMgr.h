/**
 *	> Copyright(c) 2015 guqi
 *
 *	> LIBSHARED  VERSION :		0.0.1 
 *
 *	> File Name			 :		SigEventMgr.h
 *
 *	> Author			 :		guqi
 *
 *	> Mail				 :		guqi_282@126.com
 *
 *	> Created Time		 :		2015-10
 *
 * */


#ifndef SHAERD_SIGEVENT_MANAGER_H
#define SHARED_SIGEVENT_MANAGER_H

#include <base/Singleton.h>
#include <base/Mutex.h>

namespace Shared
{

class SigEvent;

class SigEventMgr
{
public:
	SigEventMgr();
	~SigEventMgr();
public:
	void AddSigEvent(SigEvent * ev);
	SigEvent * GetSigEvent(int sig);
	void RemoveSigEvent(int sig);
	void Execute(int sig);
private:
	void Clear();
protected:
	mutable Mutex m_mutex;
	map<int,SigEvent *> m_sigmap;
};

}
#endif
