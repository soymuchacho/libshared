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
#include <utility/ObjectMgr.hpp>
#include <Event.h>

namespace Shared
{

class SigEventMgr : public Utility::ObjectMgr< int , Event >
{
public:
	SigEventMgr();
	~SigEventMgr();
public:
	bool AddSigEvent(Event * ev);
	bool GetSigEvent(int sig,event_sptr& ev);
	bool RemoveSigEvent(int sig);
	void Execute(int sig);
private:
	void Clear();
};

}
#endif
