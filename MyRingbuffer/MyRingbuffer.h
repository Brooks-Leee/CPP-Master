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
	// ��ʼ���б� ����ʹ�� std::initailizer_list ����ʼ����Ա����
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

	// �вι��� ��ʼ��дָ��λ��
	void init();

	T& get();

	// ��ͨд�룬can not write when buffer is full
	void put(T data);

	//ǿ��д�룬buffer���˺󸲸������һ��Ԫ��
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
	// �ж��Ƿ�Ϊ��
	if (!isEmpty())
	{
		int indexTemp = m_getIndex;
		// �ж��Ƿ���������ĩβ �����۷�
		if (m_getIndex == 2*m_capacity - 1)
		{
			m_getIndex = 0;
			return m_data[getRealIndex(indexTemp)];
		}
		m_getIndex++;

		// ��¼�Ƿ���
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




// ���� �ж�buffer�Ƿ�������
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

