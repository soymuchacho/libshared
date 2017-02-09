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
 * > File Name					:		Field.h
 * > Author						:		soymuchacho
 * > Created Time				:		2015-10
 * > brief						:		域 
 *
 * */

#ifndef SHARED_FIELD_H
#define SHARED_FIELD_H

#include <include/Common.h>

namespace Shared
{

class Field
{
public:
	inline void SetValue(char * value,int len) { mValue = value ; mLen = len;}
	inline int GetLength()	{return mLen;}
	inline const char * GetString()	{ return mValue; }
	inline float GetFloat()	{	return mValue ? static_cast<float>(atof(mValue)) : 0; }
	inline bool GetBool()	{	return mValue ? atoi(mValue) > 0 : false; }
	inline uint8_t GetUInt8() {	return mValue ? static_cast<uint8_t>(atol(mValue)) : 0;}
	inline int8_t GetInt8() {	return mValue ? static_cast<int8_t>(atol(mValue)) :0;}
	inline uint16_t GetUInt16() {	return mValue ? static_cast<uint16_t>(atol(mValue)) : 0; }
	inline uint32_t GetUInt32() {	return mValue ? static_cast<uint32_t>(atol(mValue)) : 0; }
	inline int32_t GetInt32()	{	return mValue ? static_cast<int32_t>(atol(mValue)) :0; }
	uint64_t GetUInt64()
	{
		uint64_t value;
		sscanf(mValue,"%I64d",&value);
		return value;
	}
private:
	char * mValue;
	int mLen;
};

}// END NAMESPACE

#endif// END SHARED_FIELD_H
