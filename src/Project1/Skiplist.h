#pragma once
#include <vector>


class SkipList {
public:
	SkipList();
	~SkipList(); 
	bool search(int target); 
	void insert(int num); 
	bool erase(int num); 

private:
	struct Node; 
	static const int level = 8; 
	void find(int target, std::vector<Node*>& pre); // ����ÿһ��С��Ŀ��ֵ�����ڵ�

	struct Node {
		int val; // �ڵ�ֵ
		std::vector<Node*> next; // ��¼�ڵ���ÿһ��� next��next[i] ��ʾ��ǰ�ڵ�� i ��� next

		Node(int _val); 
	};

	Node* head;
};