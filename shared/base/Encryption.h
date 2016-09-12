/*
 * Copyright (c) 2012-2016 soymuchacho <guqi_282@126.com>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * > LIBSHARED  VERSION 		:		0.0.1 
 * > File Name					:		Encryption.h
 * > Author						:		soymuchacho
 * > Created Time				:		2015-10
 * > brief						:		加密算法
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

