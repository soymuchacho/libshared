/**
 *	> Copyright(c) 2015 guqi
 *
 *	> LIBSHARED  VERSION :		0.0.1 
 *
 *	> File Name			 :		SigEvent.h
 *
 *	> Author			 :		guqi
 *
 *	> Mail				 :		guqi_282@126.com
 *
 *	> Created Time		 :		2015-10
 *
 * */

#ifndef SHARED_SIGNAL_EVENT_H
#define SHARED_SIGNAL_EVENT_H

#include <Event.h>

namespace Shared
{

class SigEvent
{
public:
	SigEvent()
	{
		sig_attr = EVENT_ATTR_CYCLE;	
	}

	SigEvent(Event_Attr attr)
	{
		sig_attr = attr;	
	}

	SigEvent(const SigEvent & sev)
	{
		this->sig = sev.sig;
		this->sig_attr = sev.sig_attr;
		this->handler = sev.handler;
		this->arg = sev.arg;
	}

	~SigEvent() {}
public:
	int			sig;
	Event_Attr	sig_attr;
	void		(*handler)(void *);
	void		* arg;
};


}


#endif

