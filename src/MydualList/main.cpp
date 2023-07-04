#include <iostream>
#include "MydualList.h"

int main()
{
	MyDualList<int>* myDualList = new MyDualList<int>();


	myDualList->pushback(3);
	myDualList->pushfront(2);
	myDualList->pushback(1);
	std::cout << myDualList->getSize() << std::endl;
	myDualList->print();
	myDualList->insert(200, 1);
	myDualList->print();

}