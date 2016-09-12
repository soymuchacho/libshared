/**
 *	> Copyright(c) 2015 guqi
 *
 *	> LIBSHARED  VERSION :		0.0.1 
 *
 *	> File Name			 :		Min_Heap.h
 *
 *	> Author			 :		guqi
 *
 *	> Mail				 :		guqi_282@126.com
 *
 *	> Created Time		 :		2015-10
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


