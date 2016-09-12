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
 * > File Name					:		Min_Heap.h
 * > Author						:		soymuchacho
 * > Created Time				:		2015-10
 * > brief						:		 
 *
 * */

#ifndef SHARED_MIN_HEAP_H
#define SHARED_MIN_HEAP_H

#include <base/Singleton.h>
#include <base/Mutex.h>

namespace Shared
{

class Event;

class MinHeap 
{
public:
	MinHeap();
	~MinHeap();
public:
	bool Initialize(int capacity);
	void Tick();
	bool Empty();
	void Display();
public:
	bool AddTimerEvent(Event * ev);
	bool DelTimerEvent(Event * ev);
	void ClearAllEvent();
private:
	// 下滤操作
	bool min_heap_shift_down(int hole_index);
	// 上滤操作
	bool min_heap_shift_up(int hole_index);
	// 删除元素
	bool min_heap_elm_remove();
	// 增加数组容量
	bool IncreaseCapacity();
	// 删除顶端事件
	void pop_timer();
protected:
	mutable Mutex	m_mutex;			// 保证线程安全
	Event **		m_min_heap;
	unsigned int	m_capacity;
	unsigned int	m_cursize;
};

}
#endif


