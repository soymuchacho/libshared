/**
 *	> Copyright(c) 2015 guqi
 *
 *	> LIBSHARED  VERSION :		0.0.1 
 *
 *	> File Name			 :		Random.cpp
 *
 *	> Author			 :		guqi
 *
 *	> Mail				 :		guqi_282@126.com
 *
 *	> Created Time		 :		2015-10
 *
 * */

#include <base/Random.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

namespace Shared
{

initializeSingleton( Random );

Random::Random()
{

}

Random::~Random()
{

}

// 不包括rend
int Random::GetIntRandom(int rstart,int rend)
{
	srand(time(NULL));
	return ((rand()%(rend - rstart)) + rstart); 
}

}
