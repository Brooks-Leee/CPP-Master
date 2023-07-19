#include "MyRingbuffer.h"



int main()
{

	MyRingbuffer<int> myRing = {1,2,3,4,5};
	myRing.printData();
	std::cout << myRing.get() << std::endl;
	std::cout << myRing.get() << std::endl;
	std::cout << myRing.get() << std::endl;
	std::cout << myRing.get() << std::endl;
	std::cout << myRing.get() << std::endl;
	std::cout << myRing.get() << std::endl;

	myRing.put(10);
	myRing.printData();

	myRing.put(20);
	myRing.printData();

	myRing.put(30);
	myRing.printData();

	myRing.put(40);
	myRing.printData();

	myRing.put(50);
	myRing.printData();

	myRing.put(60);
	myRing.printData();


	

}