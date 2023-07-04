#pragma once
#include <iostream>

template<typename T>
class Node
{
public:
	Node()
	{
		Prev = Next = nullptr;
	}
	Node(const T& data)
	{
		Prev = Next = nullptr;
		m_data = data;

	}
	~Node()
	{
		Prev = Next = nullptr;
	}

	Node* Prev;
	Node* Next;
	T m_data;
};


template<typename T>
class MyDualList
{
public:
	MyDualList()
	{
		head = new Node<T>();
		tail = new Node<T>();
		head->Next = tail;
		tail->Prev = head;
	}
	~MyDualList()
	{
		delete head;
		delete tail;
	}

public:
	void pushback(const T& Value);
	void pushfront(const T& Value);
	void insert(const T& Value, int index);
	Node<T>* find(const T& Value);
	bool isEmpty();
	int getSize();
	void print();

private:
	Node<T>* head;
	Node<T>* tail;
};

template<typename T>
inline void MyDualList<T>::pushback(const T& Value)
{
	Node<T>* CurrNode = new Node<T>(Value);
	
	tail->Prev->Next = CurrNode;
	CurrNode->Next = tail;
	CurrNode->Prev = tail->Prev;
	tail->Prev = CurrNode;

}

template<typename T>
inline void MyDualList<T>::pushfront(const T& Value)
{
	Node<T>* CurrNode = new Node<T>(Value);

	head->Next->Prev = CurrNode;
	CurrNode->Next = head->Next;
	CurrNode->Prev = head;
	head->Next = CurrNode;
	
}

template<typename T>
inline void MyDualList<T>::insert(const T& Value, int index)
{
	if (index > getSize())
	{
		return;
	}
	auto newNode = new Node<T>(Value);

	Node<T>* Temp = head;
	for (int i = 0; i< index + 1; i++)
	{
		Temp = Temp->Next;
	}

	newNode->Next = Temp;
	newNode->Prev = Temp->Prev;
	
	Temp->Prev->Next = newNode;
	Temp->Prev = newNode;
}

template<typename T>
inline Node<T>* MyDualList<T>::find(const T& Value)
{
	Node<T>* Temp = head;
	int index = 0;
	while (Temp->Next != tail)
	{
		Temp = Temp->Next;
		if (Temp->m_data = Value)
		{
			return Temp;
		}
		index++;
	}
	return nullptr;

}

template<typename T>
inline bool MyDualList<T>::isEmpty()
{
	if (head->Next = tail)
	 {
		return true;
	 }
}

template<typename T>
inline int MyDualList<T>::getSize()
{
	int count = 0;
	Node<T>* Temp = head;
	while (Temp->Next != tail)
	{
		count++;
		Temp = Temp->Next;
	}
	return count;
}

template<typename T>
inline void MyDualList<T>::print()
{
	int count = 0;
	Node<T>* Temp = head;
	while (Temp->Next != tail)
	{
		count++;
		Temp = Temp->Next;
		std::cout << Temp->m_data << "  ";
	}
	std::cout << std::endl;
}
