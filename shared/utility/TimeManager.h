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
 * > File Name					:		TimeManager.h
 * > Author						:		soymuchacho
 * > Created Time				:		2015-10
 * > brief						:		时间管理类 
 *
 * */

#ifndef SHARED_TIME_MANAGER_H
#define SHARED_TIME_MANAGER_H

#include <sys/time.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <common/Singleton.h>

namespace Shared
{

class TimeManager : public Singleton< TimeManager > 
{
	SINGLETON_PARENT_FRIEND(TimeManager);
private:
        struct  timeval _tstart,_tend;
        time_t  m_SetTime;
        struct  tm      m_TM;
private:
        TimeManager() 
		{ 
			m_SetTime = 0;
			memset(&m_TM,0,sizeof(m_TM));
			gettimeofday(&_tstart,NULL);
		}
        ~TimeManager() { }
public:
        unsigned int CurrentTime() 
		{
			// 相对时间，单位毫秒
			unsigned int m_CurrentTime = 0;
			gettimeofday(&_tend,NULL);
			double t1, t2;
			t1 =  (double)_tstart.tv_sec*1000 + (double)_tstart.tv_usec/1000;
			t2 =  (double)_tend.tv_sec*1000 + (double)_tend.tv_usec/1000;
			m_CurrentTime = (unsigned int)(t2-t1);
			return m_CurrentTime;
		}
		unsigned int GetLocalTime()
		{
			time_t now;
			time(&now);
			return now;
		}
		void GetTimeString(time_t timer,char * str)
		{
			struct tm *tblock;
			tblock = localtime(&timer);
			memset(str,0,64);
			snprintf(str,64,"%4d-%2d-%2d",tblock->tm_year+1900,tblock->tm_mon + 1,
					tblock->tm_mday);
		}
		int  GetAllTime(time_t t)
		{
			int ret = 0;
			struct tm tmp;
			if (t == 0)
			{
				time_t tnow = time(NULL);
				localtime_r(&tnow,&tmp);
			}
			else
			{
				time_t tnow = _tstart.tv_sec + t / 1000;
				localtime_r(&tnow,&tmp);
			}
			ret += tmp.tm_year * 100 * 100 * 100 * 100;
			ret += tmp.tm_mon  * 100 * 100 * 100;
			ret += tmp.tm_mday * 100 * 100;
			ret += tmp.tm_hour * 100;
			ret += tmp.tm_min;
			return ret;
		}
		// 最小时间是秒
		int  GetSecTime(time_t t)
		{
			int ret = 0;
			struct tm tmp;
			if(t == 0)
			{
				time_t tnow = time(NULL);
				localtime_r(&tnow,&tmp);
			}
			else
			{
				time_t tnow = _tstart.tv_sec + t / 1000;
				localtime_r(&tnow,&tmp);
			}
			ret += tmp.tm_hour * 100 * 100;
			ret += tmp.tm_min * 100;
			ret += tmp.tm_sec;
			return ret;
		}
		void    SetTime()
		{
			time(&m_SetTime);
			localtime_r(&m_SetTime,&m_TM);
		}

		int    GetTime()
		{
			SetTime();
			return m_SetTime;
		}
		//      最小单位是分钟
		int  GetDayTime(time_t t)
		{
			int ret = 0;
			struct tm tmp;
			if (t == 0)
			{
				time_t tnow = time(NULL);
				localtime_r(&tnow,&tmp);
			}
			else
			{
				time_t tnow = _tstart.tv_sec + t / 1000;
				localtime_r(&tnow,&tmp);
			}
			// ret += tmp.tm_yday * 100 * 100; // 0-3
			ret += tmp.tm_hour * 100;       // 2
			ret += tmp.tm_min;              // 2 
			return ret;
		}
		//      最小单位是分钟
		int   GetWeekTime(time_t t)
		{
			int  ret = 0;
			struct tm tmp;
			if (t == 0)
			{
				time_t tnow = time(NULL);
				localtime_r(&tnow,&tmp);
			}
			else
			{
				time_t tnow = _tstart.tv_sec + t / 1000;
				localtime_r(&tnow,&tmp);
			}
			//int a = (7 + tmp.tm_yday - tmp.tm_wday) / 7;
			//ret += a * 10 * 100 * 100;
			ret += tmp.tm_wday * 100 * 100;
			ret += tmp.tm_hour * 100;
			ret += tmp.tm_min;
			return ret;
		}

		bool    IsInOneWeek(time_t t1,time_t t2)
		{
			struct tm tmp1,tmp2;
			localtime_r(&t1,&tmp1);
			localtime_r(&t2,&tmp2);
			if(tmp1.tm_year != tmp2.tm_year)
				return false;
			int yd = tmp1.tm_yday - tmp2.tm_yday;
			int wd = tmp1.tm_wday + yd;
			if(wd < 0 || wd >= 7)
				return false;
			return true;
		}

		bool    IsInOneDay(time_t t1,time_t t2)
		{
			struct tm tmp1,tmp2;
			localtime_r(&t1,&tmp1);
			localtime_r(&t2,&tmp2);
			if(tmp1.tm_yday == tmp2.tm_yday && tmp1.tm_year == tmp2.tm_year)
				return true;
			return false;
		}

		// check by GetWeekTime()...
		bool    IsInOneWeek_All(int t1,int t2)
		{
			// Get Week Num;
			int w1 = t1 / 10 * 100 * 100;
			int w2 = t2 / 10 * 100 * 100;
			if(w1 == w2)
				return true;
			else
				return false;
		}

		// check by GetDayTime()...
		bool    IsInOneDay_All(int t1,int t2)
		{
			int d1 = t1 / 100 * 100;
			int d2 = t2 / 100 * 100;
			return (d1 == d2);
		}
};

static inline TimeManager & Shared_TimeManager()
{
	return TimeManager::getSingleton();
}

static unsigned int CURRENTTIME()
{
	return TimeManager::getSingleton().CurrentTime();
}

}// END NAMESPACE SHARED
#endif
