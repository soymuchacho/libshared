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
 * > File Name					:		demo.cpp
 * > Author						:		soymuchacho
 * > Created Time				:		2017年02月24日 星期五 16时00分08秒
 * > brief						:		
 *
 * */

#include <stdio.h>
#include <iostream>
#include <pyscript/pyscript.h>
#include <common/MemoryPool.h>
#include <common/Log.h>
using namespace std;


int main()
{
    Shared::Shared_Log().Initialize("output",Shared::LOG_DEBUG);
    Shared::PYSCRIPT::pyscript * pt = Shared::MM_NEW<Shared::PYSCRIPT::pyscript>();
    if(pt == NULL)
    {
        LOGDEBUG("demo","malloc error!");
        return 0;
    }
    LOGDEBUG("demo","begin pyscript!");    
    string path = "./python";
    pt->Initialize(path.c_str());

    Shared::PYSCRIPT::PyRet * ret = pt->CallFunction<char *>("sayHi",(char *)"myname");
    Shared::PYSCRIPT::PyRet * ret2 = pt->CallFunction<int,int>("myfunc",1,2);
    if(ret != NULL)
    {
        LOGDEBUG("debug","ret != NULL");
        Shared::MM_DELETE(ret);
    }

    if(ret2 != NULL)
    {
        LOGDEBUG("demo","myfunc result : %d",ret2->GetInt());
        Shared::MM_DELETE(ret2);
    }
    pt->Release();
    getchar();
    return 0;
}


