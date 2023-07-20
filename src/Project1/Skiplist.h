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
	void find(int target, std::vector<Node*>& pre); // 查找每一层小于目标值的最大节点

	struct Node {
		int val; // 节点值
		std::vector<Node*> next; // 记录节点在每一层的 next，next[i] 表示当前节点第 i 层的 next

		Node(int _val); 
	};

	Node* head;
};