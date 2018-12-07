#pragma once
#include <vector>
#include <iostream>
#include<Eigen/Dense>

using namespace std;
using namespace Eigen;

class vertex
{
public:
	vertex();
	vertex(const vertex &other);
	bool operator==(const vertex &other);
	~vertex();

	float distance;
	int id;
	short int cout = 0;
	Vector3f loc;
};

