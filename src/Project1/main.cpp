#include "Skiplist.h"
#include <iostream>


int main()
{
	SkipList skiplist;
	skiplist.insert(1);
	skiplist.insert(2);
	skiplist.insert(3);
	std::cout << skiplist.search(0) << std::endl;   
	skiplist.insert(4);
	std::cout << skiplist.search(1) << std::endl;   
	skiplist.erase(0);    // 返回 false，0 不在跳表中
	skiplist.erase(1);    // 返回 true
	std::cout << skiplist.search(1) << std::endl;   // 返回 false，1 已被擦除

}