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
 * > File Name					:		Min_Heap.cpp
 * > Author						:		soymuchacho
 * > Created Time				:		2015-10
 * > brief						:		最小堆，时间管理器 
 *
 * */

/**
 *	> Copyright(c) 2015 guqi
 *
 *	> LIBSHARED  VERSION :		0.0.1 
 *
 *	> File Name			 :		Min_Heap.cpp
 *
 *	> Author			 :		guqi
 *
 *	> Mail				 :		guqi_282@126.com
 *
 *	> Created Time		 :		2015-10
 *
 * */

#include <network/Min_Heap.h>
#include <network/MemoryPool.h>
#include <Event.h>
#include <base/Log.h>
#include <utility/TimeManager.h>

namespace Shared
{

initializeSingleton(MinHeap);

MinHeap::MinHeap()
{
	bool ret = Initialize(10);
	ASSERT(ret == true);
}

MinHeap::~MinHeap()
{
	ClearAllEvent();
}

bool MinHeap::Initialize(int capacity)
{
	m_cursize = 0;
	m_capacity = capacity;
	m_min_heap = new Event *[m_capacity];
	if(m_min_heap == NULL)
	{
		LOGDWORN("debug","heap malloc error!");
		return false;
	}
	for(int i = 0; i < m_capacity;i++)
	{
		m_min_heap[i] = NULL;
	}
	return true;
}

bool MinHeap::AddTimerEvent(Event * ev)
{
	MutexLockGuard guard(&m_mutex);
	
	if(m_cursize + 1 > m_capacity)
	{
		IncreaseCapacity();
	}

	m_min_heap[m_cursize] = ev;
	// 上滤操作
	min_heap_shift_up(m_cursize);
	m_cursize++;
	return true;
}

bool MinHeap::DelTimerEvent(Event * ev)
{
	MutexLockGuard guard(&m_mutex);
	// 将时间间隔置为 0 , 回调函数 置为NULL
	// 延迟消除
	ev->m_interval = 0;
	ev->m_call = NULL;
	return true;
}

void MinHeap::ClearAllEvent()
{
	for(int i = 0; i < m_cursize; i++)
	{
		MM_DELETE(m_min_heap[i]);
	}
	delete [] m_min_heap;
	m_cursize = 0;
}

bool MinHeap::min_heap_shift_down(int hole_index)
{
	// 堆下滤操作！
	int child_index = 0;

	Event * event = m_min_heap[hole_index];

	if(event == NULL)
	{
		LOGDEBUG("debug","min_heap_shift_down : event = null");
		return false;
	}

	for(;(hole_index * 2 + 1) < m_cursize;hole_index = child_index)
	{
		child_index = hole_index * 2 + 1;
		if(m_min_heap[child_index] == NULL)
			break;
		if(child_index < (m_cursize - 1) && m_min_heap[child_index + 1]->m_alarm < m_min_heap[child_index]->m_alarm)
		{
			++child_index;
		}

		if (m_min_heap[child_index]->m_alarm < event->m_alarm)
		{
			m_min_heap[hole_index] = m_min_heap[child_index];
		}
		else
			break;
	}
	m_min_heap[hole_index] = event;
	return true;
}

bool MinHeap::min_heap_shift_up(int hole_index)
{
	// 堆上滤操作！
	int father_index = 0;
	
	Event * event = m_min_heap[hole_index];
	
	if(event == NULL)
	{
		LOGDEBUG("debug","min_heap_shift_down : event = null");
		return false;
	}

	for(;hole_index > 0; hole_index = father_index)
	{
		father_index = (hole_index - 1) / 2;
		if(m_min_heap[father_index] == NULL)
			break;
		if( event->m_alarm >= m_min_heap[father_index]->m_alarm)
		{
			break;
		}
		m_min_heap[hole_index] = m_min_heap[father_index];
	}
	m_min_heap[hole_index] = event;

	return true;
}

bool MinHeap::IncreaseCapacity()
{
	int capacity = m_capacity * 2;
	Event ** min_heap = new Event*[capacity];
	if(min_heap == NULL)
	{
		LOGDWORN("debug","min_heap malloc error!");
		return false;
	}
	
	for(int i = 0; i < capacity; i++)
	{
		if(i < m_cursize)
			min_heap[i] = m_min_heap[i];
		else
			min_heap[i] = NULL;
	}

	m_capacity = capacity;
	delete [] m_min_heap;
	m_min_heap = min_heap;
	min_heap = NULL;
	return true;
}

void MinHeap::pop_timer()
{
	if( Empty() )
		return;
	MutexLockGuard guard(&m_mutex);
	Event * event = m_min_heap[0];

	if(event != NULL)
	{
		if(event->m_attr == EVENT_ATTR_CYCLE)	
		{
			event->m_alarm += event->m_interval;
		}
		else
		{
			MM_DELETE(event);
			m_min_heap[0] = m_min_heap[--m_cursize];
			m_min_heap[m_cursize] = NULL;
		}
		// 下滤操作
		min_heap_shift_down(0);
	}
	else
	{
		m_min_heap[0] = m_min_heap[--m_cursize];
		m_min_heap[m_cursize] = NULL;
		// 下滤操作
		min_heap_shift_down(0);
	}
}

bool MinHeap::Empty()
{
	if(m_cursize == 0)
		return true;
	return false;
}

void MinHeap::Tick()
{
	Event * event = m_min_heap[0];	
	time_t now_time = CURRENTTIME();
	while(!Empty())
	{
		if(event == NULL)
			break;
		if(event->m_alarm > now_time)
			break;
		if(event->m_interval == 0)
		{
			// 此event需要删除
			m_min_heap[0] = NULL;
			pop_timer();
			// 将event销毁，只此一处销毁，其他地方不能销毁该event
			MM_DELETE(event);
			break;
		}
		if(event->m_call)
			event->m_call(event->m_fd,event->m_arg,event->m_args);
		pop_timer();
		event = m_min_heap[0];
	}
}

void MinHeap::Display()
{
	for(int i = 0; i < m_cursize;i++)
	{
		if(m_min_heap[i] == NULL)
			LOG2("L","MINHEAP","[%d(null)] ",i);
		else
			LOG2("L","MINHEAP","[%d(%u)]",i,m_min_heap[i]->m_alarm);
	}
	LOG2("L","MINHEAP","----------------------------------");
}

}
