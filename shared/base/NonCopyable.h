/**
 *	> Copyright(c) 2015 guqi
 *
 *	> LIBSHARED  VERSION :		0.0.1 
 *
 *	> File Name			 :		NonCopyable.h
 *
 *	> Author			 :		guqi
 *
 *	> Mail				 :		guqi_282@126.com
 *
 *	> Created Time		 :		2015-12
 *
 * */

#ifndef SHARED_NON_COPYABLE_H
#define SHARED_NON_COPYABLE_H

namespace Shared
{

class noncopyable
{
protected:
	noncopyable() {}
	~noncopyable(){}
private:
	noncopyable(const noncopyable &);
	noncopyable & operator=(const noncopyable &);
};

}
#endif

