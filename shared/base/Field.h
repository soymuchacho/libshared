/**
 *	> Copyright(c) 2015 guqi
 *
 *	> LIBSHARED  VERSION :		0.0.1 
 *
 *	> File Name			 :		Field.h
 *
 *	> Author			 :		guqi
 *
 *	> Mail				 :		guqi_282@126.com
 *
 *	> Created Time		 :		2015-10
 *
 * */

#ifndef SHARED_FIELD_H
#define SHARED_FIELD_H

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
