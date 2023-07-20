#pragma once

#include <vector>
#include <memory>


#define MAX_DEPTH  5
#define MAX_COUNT 20


class FVector3
{
public:
	FVector3(){}
	FVector3(float x, float y, float z): x(x), y(y), z(z){}
	FVector3(const FVector3& other) : x(other.x), y(other.y), z(other.z) {}

public:
	float x = 0;
	float y = 0;
	float z = 0;

};

class MyOctreeNode
{
public:
	MyOctreeNode(){}
	MyOctreeNode(FVector3 center, float extend, int depth) : m_center(center), m_extend(extend), m_depth(depth)
	{
		m_arrChildren.resize(8);
		for (int i = 0; i < 8; i++)
		{
			m_arrChildren[i] = nullptr;
		}
	}
	~MyOctreeNode(){}


public:
	void subdivide();
	void insert(FVector3  point);
	bool find(FVector3 point);


private:
	int getIndex(const FVector3& point);
	bool InterSection(const FVector3& point);

public:
	
	FVector3 m_center;  // box的中心坐标
	float m_extend; 	// box的边长
	int m_maxCount = MAX_COUNT;  // 单个box所能存储的最大objects数量
	int m_depth = MAX_DEPTH;  // octree最大深度


	std::vector<FVector3> m_arrObjs;  // objects 数组
	std::vector<std::shared_ptr<MyOctreeNode>> m_arrChildren;  // octree节点数组
	 
};

