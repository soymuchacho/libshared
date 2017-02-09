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
 * > File Name					:		Mutex.cpp
 * > Author						:		soymuchacho
 * > Created Time				:		2015-10
 * > brief						:		互斥锁 
 *
 * */

#include <base/Mutex.h>
#include <base/Log.h>

namespace Shared
{

Mutex::Mutex()
{
	pthread_mutex_init(&m_mutex,NULL);
}

Mutex::~Mutex()
{
	pthread_mutex_destroy(&m_mutex);
}

void Mutex::Lock()
{
	pthread_mutex_lock(&m_mutex);
}

void Mutex::UnLock()
{
	pthread_mutex_unlock(&m_mutex);
}

void Mutex::Acquire()
{
	Lock();
}

void Mutex::Release()
{
	UnLock();
}

bool Mutex::AttemptAcquire()
{
	if(!pthread_mutex_trylock(&m_mutex))
		return true;
	else 
		return false;
}

}