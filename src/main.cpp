#include<iostream>
#include "MyString.h"


int main()
{
	MyString defualtStr = MyString();

	MyString paramStr =  MyString("wow");

	MyString cpyConstructStr = MyString(paramStr);

	MyString equalMyStr = paramStr;

	MyString equalCharStr = "wow";
	
	bool boolTest = paramStr == equalCharStr;


	std::cout << "  default construct: -----> " << defualtStr << std::endl;
	std::cout << "  param construct: -------> " << paramStr << std::endl;
	std::cout << "  copy construct: --------> " << cpyConstructStr << std::endl;
	std::cout << "  = MyString test: -------> " << equalMyStr << std::endl;
	std::cout << "  = char* test: ----------> " << equalCharStr << std::endl;
	std::cout << "  bool test: -------------> " << boolTest << std::endl;
	paramStr.append("+wow");
	std::cout << "  append test: -----------> " << paramStr << std::endl;
	std::cout << "  len test: --------------> " << paramStr.len() << std::endl;
	std::cout << "  find (ow) test: --------> " << paramStr.find("ow") << std::endl;
	std::cout << "  find (oww) test: -------> " << paramStr.find("oww") << std::endl;
	MyString subStr = paramStr.sub(1, 4);
	std::cout << "  sub test: --------------> " << subStr << std::endl;


}