/*
 * Copyright (c) 2012-2016 soymuchacho <guqi_282@126.com>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
#ifndef _PY_CONFIG_H
#define _PY_CONFIG_H
#endif
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
 * > File Name					:		py_config.h
 * > Author						:		soymuchacho
 * > Created Time				:		2016年12月16日 星期五 11时39分15秒
 * > brief						:		和python相关的配置
 *
 * */

#ifndef SHARED_PYTHON_CONFIG_H
#define SHARED_PYTHON_CONFIG_H

namespace Shared
{

namespace PYSCRIPT
{

#include <string>
using namespace std;

// typeid.name 类型string对应python类型string
typedef struct type_c_to_python_info
{
    string typeid_name;
    string python_type;
}TYPE_C_TO_PYTHON_INFO;

static TYPE_C_TO_PYTHON_INFO type_info[]
{
    // string [char *]
    {"Pc","s"},
    {"PKc","s"},
    // string [char *,int] convert a C string and its length to a Python object.
    // if the C string pointer is NULL, the length is ignored and None is returned.
    //{"","s#"},
    // z (string or None) [char *] same as s
    //{"","z"},
    // same as s#
    //{"","z#"},
    // Unicode string [Py_UNICODE *]
    //{"","u"},
    // (Unicode string) [Py_UNICODE *,int]
    //{"","u#"},
    // (integer) [int]
    {"i","i"},
    // (integer) [char]
    {"c","b"},
    // (integer) [short int]
    {"s","h"},
    // (integer) [long int]
    {"l","l"},
    // (integer) [unsigned char]
    {"h","B"},
    // (integer) [unsigned short int]
    {"t","H"},
    // (integer/long) [unsigned int]
    {"j","I"},
    // (integer/long) [unsigned int]
    //{"","k"},
    // (integer/long) [unsigned int]
    //{"","k"},
    // (long) [PY_LONG_LONG]
    //{"l","L"},
    // (long) [unsigned PY_LONG_LONG]
    {"x","K"},
    // (int) [Py_ssize_t]
    //{"","n"},
    // (string of length 1) [char]
    {"a","c"},
    // (float) [double]
    {"d","d"},
    // (float) [float]
    {"f","f"},
    // (complex) [Py_complex *] Convert a C Pycomplex structure to a Python complex number.
    //{"","D"},
    // (object) [Py_Object *]
    {"","O"},
    // (Object) [PyObject *] same as O
    //{"","S"},
    // (object) [PyObject *] same as 0
    //{"","N"},
    // (object) [converter, anything]
    //{"","O&"},
    // (tuple) [matching-items]
    //{"","(items)"},
    // (list) [maching-items]
    //{"","[items]"},
    // (dictionary) [maching-items]
    //{"","{items}"},
};

static std::string GetTypeStr(string strType)
{
    int size = sizeof(type_info)/sizeof(TYPE_C_TO_PYTHON_INFO);
    for(int i = 0; i < size; i++)
    {
        if(type_info[i].typeid_name.compare(strType) == 0)
        {
            return type_info[i].python_type;
        }
    }
    return "O";
}

}

}

#endif

