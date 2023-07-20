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
	skiplist.erase(0);    // ���� false��0 ����������
	skiplist.erase(1);    // ���� true
	std::cout << skiplist.search(1) << std::endl;   // ���� false��1 �ѱ�����

}