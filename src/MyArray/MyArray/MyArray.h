#include <algorithm>
#include <iostream>

template <typename T>
class MyArray
{
public:
	// default construct
	MyArray() : m_size(0), m_capacity(1), m_data(new T[10]){}
	MyArray(int capacity) : m_size(0), m_capacity(capacity), m_data(new T[capacity]){}
	// copy construct
	MyArray(const MyArray& other)
	{
		m_size = other.m_size;
		m_capacity = other.m_capacity;
		std::copy(other.m_data, other.m_data + other.m_size, m_data);
	}
	// move construct
	MyArray(MyArray&& other)
	{
		m_size = other.m_size;
		m_capacity = other.m_capacity;
		m_data = other.m_data;

		// std::move 后会把other指针置空，需要把other里面的东西清除，否则就内存泄漏了
		other.m_size = 0;
		other.m_capacity = 0;
		other.m_data = nullptr;
	}

	~MyArray()
	{
		delete[] m_data;
	}

	void reverse();
	void print();
	void push(const T& data);
	void insert(int index, const T& data);
	void remove(int index);
	void pop();
	void clear();
	int find(const T& value) const;

private:
	void resize(int capacity);


private:
	int m_size;
	int m_capacity;
	T* m_data;
};






template<typename T>
void MyArray<T>::reverse()
{
	for (int left = 0, right = m_size - 1; left < right; left++, right--)
	{
		std::swap(m_data[left], m_data[right]);
	}
}

template<typename T>
void MyArray<T>::push(const T& data)
{
	if (++m_size >= m_capacity)
	{
		resize(m_capacity*2);
	}
	m_data[m_size - 1] = data;
}

template<typename T>
void MyArray<T>::print()
{
	for (int i = 0; i < m_size; i++)
	{
		std::cout << *(m_data + i) << " ";
	}
	std::cout << "\n" << std::endl;
}

template<typename T>
void MyArray<T>::insert(int index, const T& data)
{ 
	if (index >= 0 && index <= m_size)
	{
		if (m_size == m_capacity)
		{
			resize(m_capacity*2);
		}
		//std::copy_backward(m_data + index, m_data + m_size, m_data + m_size + 1);
		std::copy(m_data + index, m_data + m_size, m_data + index + 1);
		m_data[index] = data;
		m_size++;
	}
}

template<typename T>
inline void MyArray<T>::remove(int index)
{
	if (index >= 0 && index <= m_size)
	{
		//delete m_data+index;
		std::copy(m_data+index+1, m_data+m_size, m_data+index);
		m_size--;
	}
}

template<typename T>
inline void MyArray<T>::pop()
{
	if (m_size > 0)
	{
		m_size--;
	}
}

template<typename T>
inline void MyArray<T>::clear()
{
	m_size = 0;
	m_capacity = 0;
	delete m_data;
}

template<typename T>
inline int MyArray<T>::find(const T& value) const
{
	for (int i = 0; i < m_size; i++)
	{
		if (m_data[i] == value)
		{
			return i;
		}
	}
	return -1;
}

template<typename T>
void MyArray<T>::resize(int capacity)
{
	if (capacity > m_capacity)
	{
		T* new_myArr = new T[capacity];
		std::copy(m_data, m_data + m_size, new_myArr);
		
		delete[] m_data;
		m_capacity = capacity;
		m_data = new_myArr;
	}
}
