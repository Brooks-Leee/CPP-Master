#include "MyOctree.h"


void MyOctreeNode::subdivide()
{
	m_arrChildren.reserve(8);
	for (int i = 0; i < 8; i++)
	{
		m_arrChildren[i] = nullptr;
	}

	float half_extend = m_extend / 2.0;

	for (int i = 0; i < 8; i++)
	{
		// 使用位运算 
		FVector3 center;
		center.x = m_center.x + ((i & 1) ? half_extend : -half_extend);
		center.y = m_center.y + ((i & 2) ? half_extend : -half_extend);
		center.z = m_center.z + ((i & 4) ? half_extend : -half_extend);

		m_arrChildren.push_back(std::make_shared<MyOctreeNode>(center, half_extend, m_depth + 1));
	}

	for (const auto& obj : m_arrObjs)
	{
		int index = getIndex(obj);
		if (index != -1)
		{
			m_arrChildren[index]->insert(obj);
		}
	}

	// 修正：重新分配数据给子节点后，清空当前节点的数据
	m_arrObjs.clear();
}


void MyOctreeNode::insert(FVector3 point)
{
	// 如果不在当前节点范围内，则直接返回
	if (!InterSection(point))
	{
		return;
	}

	// 如果不是叶子节点，则递归往下插入
	if (m_arrChildren[0] != nullptr)
	{
		int index = getIndex(point);
		if (index != -1)
		{
			m_arrChildren[index]->insert(point);
			return;
		}
	}

	// 如果是叶子节点, 点数组存满，且深度没有到最大
	m_arrObjs.push_back(point);
	if (m_arrChildren[0] == nullptr && m_arrObjs.size() > m_maxCount && m_depth < MAX_DEPTH)
	{
		subdivide();
	}


}

bool MyOctreeNode::find(FVector3 point)
{

	// 如果不在当前节点范围内，则直接返回
	if (!InterSection(point))
	{
		return false;
	}


	int index = getIndex(point);
	if (index == -1)
	{
		return false;
	}
	if (m_arrChildren[0] != nullptr)
	{
		return m_arrChildren[index]->find(point); 
	}
	else
	{
		for (const auto& obj : m_arrObjs) 
		{
			if (point.x == obj.x && point.y == obj.y && point.z == obj.z)
			{
				return true; 
			}
		}
	}

	return false;
}


// 根据点的位置确定其应该插入到哪个子立方体中
int MyOctreeNode::getIndex(const FVector3& point)
{
	// 默认为 -1 ，如果不在立方体内，返回-1
	int index = -1;

	bool is_left = point.x >= m_center.x;
	bool is_bottom = point.y >= m_center.y;
	bool is_back = point.z >= m_center.z;

	if (is_left) {
		if (is_bottom) {
			if (is_back) {
				index = 0; // 左下后
			}
			else {
				index = 4; // 左下前
			}
		}
		else {
			if (is_back) {
				index = 3; // 左上后
			}
			else {
				index = 7; // 左上前
			}
		}
	}
	else {
		if (is_bottom) {
			if (is_back) {
				index = 1; // 右下后
			}
			else {
				index = 5; // 右下前
			}
		}
		else {
			if (is_back) {
				index = 2; // 右上后
			}
			else {
				index = 6; // 右上前
			}
		}
	}

	return index;

	// GPT写的位运算方法 ————  我是肯定想不出来
	/*
	return (point.X <= center.X ? 0 : 1) +
		(point.Y >= center.Y ? 0 : 4) +
		(point.Z <= center.Z ? 0 : 2);
	*/
}

bool MyOctreeNode::InterSection(const FVector3& point)
{
	float half_extend = m_extend / 2.0;
	bool is_inside_x = (point.x >= (m_center.x - half_extend)) && (point.x <= (m_center.x + half_extend));
	bool is_inside_y = (point.y >= (m_center.y - half_extend)) && (point.y <= (m_center.y + half_extend));
	bool is_inside_z = (point.z >= (m_center.z - half_extend)) && (point.z <= (m_center.z + half_extend));
	return is_inside_x && is_inside_y && is_inside_z;
}
