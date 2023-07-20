#include "iostream"
#include "MyOctree.h"
#include <string>



int main() {

	FVector3 point(0, 0, 0);
	MyOctreeNode Octree(point, 300, 5);

	Octree.insert(FVector3(1, 10, 60));
	Octree.insert(FVector3(20, 10, 10));
	Octree.insert(FVector3(70, 60, 20));
	Octree.insert(FVector3(25, 30, 90));

	FVector3 findPoint(20, 10, 10);
	bool result = Octree.find(findPoint);
	std::cout << "findPoint" << ":" << result << std::endl;
}
