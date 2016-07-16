/**
 *	> Copyright(c) 2015 guqi
 *
 *	> LIBSHARED  VERSION :		0.0.1 
 *
 *	> File Name			 :		Encryption.h
 *
 *	> Author			 :		guqi
 *
 *	> Mail				 :		guqi_282@126.com
 *
 *	> Created Time		 :		2015-10
 *
 * */


#ifndef SHARED_ENCRYPTION_H
#define SHARED_ENCRYPTION_H

#include <include/Common.h>

namespace Shared
{

#define ENCRYPTDATA 1

static bool MixData(unsigned char * buff,int size)
{
	bool bRet = false;
#if ENCRYPTDATA 
	uint8_t tmp;

	if(NULL != buff && 0 != size)
	{
		static uint8_t codeTable[] = "!WyCnh^YNJ()OL<24jgrt7&^&$DFJmjTR<>";
		for(int i = 0; i < size; i ++)
		{
			tmp = buff[i];
			tmp ^= codeTable[((size - i)%sizeof(codeTable))];
			tmp = ~tmp;
			buff[i] = tmp;
		}
		bRet = true;
	}
#endif
	return bRet;
}

}// END NAMESPACE

#endif// END SHARED_ENCRYPTION_H

