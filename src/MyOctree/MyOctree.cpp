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
		// ʹ��λ���� 
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

	// ���������·������ݸ��ӽڵ����յ�ǰ�ڵ������
	m_arrObjs.clear();
}


void MyOctreeNode::insert(FVector3 point)
{
	// ������ڵ�ǰ�ڵ㷶Χ�ڣ���ֱ�ӷ���
	if (!InterSection(point))
	{
		return;
	}

	// �������Ҷ�ӽڵ㣬��ݹ����²���
	if (m_arrChildren[0] != nullptr)
	{
		int index = getIndex(point);
		if (index != -1)
		{
			m_arrChildren[index]->insert(point);
			return;
		}
	}

	// �����Ҷ�ӽڵ�, ����������������û�е����
	m_arrObjs.push_back(point);
	if (m_arrChildren[0] == nullptr && m_arrObjs.size() > m_maxCount && m_depth < MAX_DEPTH)
	{
		subdivide();
	}


}

bool MyOctreeNode::find(FVector3 point)
{

	// ������ڵ�ǰ�ڵ㷶Χ�ڣ���ֱ�ӷ���
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


// ���ݵ��λ��ȷ����Ӧ�ò��뵽�ĸ�����������
int MyOctreeNode::getIndex(const FVector3& point)
{
	// Ĭ��Ϊ -1 ����������������ڣ�����-1
	int index = -1;

	bool is_left = point.x >= m_center.x;
	bool is_bottom = point.y >= m_center.y;
	bool is_back = point.z >= m_center.z;

	if (is_left) {
		if (is_bottom) {
			if (is_back) {
				index = 0; // ���º�
			}
			else {
				index = 4; // ����ǰ
			}
		}
		else {
			if (is_back) {
				index = 3; // ���Ϻ�
			}
			else {
				index = 7; // ����ǰ
			}
		}
	}
	else {
		if (is_bottom) {
			if (is_back) {
				index = 1; // ���º�
			}
			else {
				index = 5; // ����ǰ
			}
		}
		else {
			if (is_back) {
				index = 2; // ���Ϻ�
			}
			else {
				index = 6; // ����ǰ
			}
		}
	}

	return index;

	// GPTд��λ���㷽�� ��������  ���ǿ϶��벻����
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
