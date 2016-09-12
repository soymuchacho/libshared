/**
 *	> Copyright(c) 2015 guqi
 *
 *	> LIBSHARED  VERSION :		0.0.1 
 *
 *	> File Name			 :		Singleton.h
 *
 *	> Author			 :		guqi
 *
 *	> Mail				 :		guqi_282@126.com
 *
 *	> Created Time		 :		2015-10
 *
 * */


#ifndef SHARED_SINGLETON_H
#define SHARED_SINGLETON_H

#include <include/Common.h>
#include <base/NonCopyable.h>

namespace Shared
{

#define initializeSingleton(type) \
	template<> type * Shared::Singleton<type>::mSingleton = 0;\
	template<> pthread_once_t Shared::Singleton<type>::ponce_ = PTHREAD_ONCE_INIT

template<class type>
class Singleton : public noncopyable
{
protected:
	Singleton()
	{
	}

	~Singleton()
	{
	}
public:
	inline static type & getSingleton()
	{
		pthread_once(&ponce_, &Singleton::init);
		return (*mSingleton);
	}
private:
	static void init()
	{
		mSingleton = new type;
		ASSERT(mSingleton != NULL);
	}
private:
	static type *			mSingleton;
	static pthread_once_t	ponce_;
};

}
#endif
