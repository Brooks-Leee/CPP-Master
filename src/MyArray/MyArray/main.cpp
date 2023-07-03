#include <iostream>
#include <string>
#include "MyArray.h"


int main()
{
	auto myArr = new MyArray<int>();
	myArr->push(3);
	myArr->push(5);
	myArr->push(6);
	myArr->push(7);
	myArr->print();
	myArr->reverse();
	myArr->print();
	myArr->insert(1, 100);
	myArr->print();
	myArr->remove(3);
	myArr->print();
	myArr->pop();
	myArr->print();
	std::cout << "find value:100 in index : " << myArr->find(100) << std::endl;
	myArr->clear();
}