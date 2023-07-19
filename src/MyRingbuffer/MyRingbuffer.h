#pragma once
#include <string.h>
#include <initializer_list>
#include <iostream>
#include <vector>
#include <cassert>


template <typename T>
class MyRingbuffer
{
public:
	// default construct
	MyRingbuffer() : m_capacity(10),
		m_putIndex(0),
		m_getIndex(0),
		m_IsGetMirror(false),
		m_IsPutMirror(false),
		m_data(10)
		{}

	// param construct
	// 初始化列表 可以使用 std::initailizer_list 来初始化成员数组
	MyRingbuffer(std::initializer_list<T> data) : m_capacity(data.size()),
		m_putIndex(0),
		m_getIndex(0),
		m_IsGetMirror(false),
		m_IsPutMirror(false),
		m_data(data)
	{
		init();
		assert(data.size() > 1 && "size must be greater than 1");
	}


	~MyRingbuffer(){};


public:
	void printData();

	// 有参构造 初始化写指针位置
	void init();

	T& get();

	// 普通写入，can not write when buffer is full
	void put(T data);

	//强制写入，buffer满了后覆盖最早的一个元素
	void put_force(T data);

private:
	bool isFull();
	bool isEmpty();
	int getRealIndex(int mirrorIndex);


private:
	std::vector<T> m_data;
	int m_putIndex;
	int m_getIndex;
	bool m_IsPutMirror;
	bool m_IsGetMirror;
	int m_capacity;
};

template<typename T>
inline void MyRingbuffer<T>::printData()
{
	for (int i = 0; i < m_capacity; i++)
	{
		std::cout << m_data[i] << " ";
	}

	std::cout << std::endl;
}

template<typename T>
inline void MyRingbuffer<T>::init()
{
	m_putIndex = m_capacity - 1;
}

template<typename T>
inline T& MyRingbuffer<T>::get()
{
	// 判断是否为空
	if (!isEmpty())
	{
		int indexTemp = m_getIndex;
		// 判断是否碰到数组末尾 是则折返
		if (m_getIndex == 2*m_capacity - 1)
		{
			m_getIndex = 0;
			return m_data[getRealIndex(indexTemp)];
		}
		m_getIndex++;

		// 记录是否镜像
		if (m_getIndex > m_capacity -1)
		{
			m_IsGetMirror = true;
		}
		else
		{
			m_IsGetMirror = false;
		}

		return m_data[getRealIndex(indexTemp)];
	}
	else
	{
		std::cout << "Buffer Is Empty" << std::endl;
		return m_data[getRealIndex(m_getIndex)];
	}

}

template<typename T>
inline void MyRingbuffer<T>::put(T data)
{
	if (!isFull())
	{
		m_data[getRealIndex(m_putIndex)] = data;
		if (m_putIndex == 2*m_capacity - 1)
		{
			m_putIndex = 0;
			return;
		}
		m_putIndex++;

		if (m_putIndex > m_capacity - 1)
		{
			m_IsPutMirror = true;
		}
		else
		{
			m_IsPutMirror = false;
		}

	}
	else
	{
		std::cout << "Buffer is full" << std::endl;
	}

}




// 镜像法 判断buffer是否是满的
template<typename T>
inline bool MyRingbuffer<T>::isFull()
{
	if (abs(getRealIndex(m_putIndex) - getRealIndex(m_getIndex)) == 0 && m_IsGetMirror != m_IsPutMirror)
	{
		return true;
	}
	return false;

}

template<typename T>
inline bool MyRingbuffer<T>::isEmpty()
{
	if (abs(getRealIndex(m_putIndex) - getRealIndex(m_getIndex)) == 0 && m_IsGetMirror == m_IsPutMirror)
	{
		return true;
	}
	return false;
}

template<typename T>
inline int MyRingbuffer<T>::getRealIndex(int mirrorIndex)
{
	return mirrorIndex % m_capacity;
}

