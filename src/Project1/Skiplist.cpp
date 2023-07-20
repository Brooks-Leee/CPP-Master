#include "Skiplist.h"
#include <random>

float P_FACTOR = 0.5;


SkipList::Node::Node(int _val) : val(_val) {
	next.resize(level, nullptr); // 初始化 next 数组的大小和层数 level 相同，初始值都指向 nullptr
}


SkipList::SkipList() {
	head = new Node(-1); // 初始化
}


SkipList::~SkipList() {
	Node* p = head;
	while (p) {
		Node* next = p->next[0];
		delete p;
		p = next;
	}
}

bool SkipList::search(int target) {
	std::vector<Node*> pre(level);
	find(target, pre);

	Node* p = pre[0]->next[0];
	return p && p->val == target;
}

//查找每一层小于目标值的最大节点
void SkipList::find(int target, std::vector<Node*>& pre) {
	Node* p = head;
	for (int i = level - 1; i >= 0; i--) {
		while (p->next[i] && p->next[i]->val < target) {
			p = p->next[i];
		}
		pre[i] = p;
	}
}


void SkipList::insert(int num) {
	std::vector<Node*> pre(level);
	find(num, pre);

	Node* p = new Node(num);
	for (int i = 0; i < level; i++) {
		p->next[i] = pre[i]->next[i];
		pre[i]->next[i] = p;
		if (rand() / RAND_MAX > P_FACTOR)
			break;
	}
}


bool SkipList::erase(int num) {
	std::vector<Node*> pre(level);
	find(num, pre);

	Node* p = pre[0]->next[0];
	if (!p || p->val != num)
		return false;

	for (int i = 0; i < level && pre[i]->next[i] == p; i++) {
		pre[i]->next[i] = p->next[i];
	}

	delete p;
	return true;
}