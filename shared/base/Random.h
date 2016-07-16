/**
 *	> Copyright(c) 2015 guqi
 *
 *	> LIBSHARED  VERSION :		0.0.1 
 *
 *	> File Name			 :		Random.h
 *
 *	> Author			 :		guqi
 *
 *	> Mail				 :		guqi_282@126.com
 *
 *	> Created Time		 :		2015-10
 *
 * */

#ifndef SHARED_RANDOM_H
#define SHARED_RANDOM_H

#include <base/Singleton.h>

namespace Shared
{

class Random : public Singleton< Random >
{
	friend class Singleton< Random >;
private:
	Random();
	~Random();
public:
	static int GetIntRandom(int rstart,int rend);
};

static Random & Shared_Random()
{
	return Random::getSingleton();
}

}

#endif

