#pragma once

#include "Triangle.h"
#include <vector>
#include <iostream>
class BVHNode
{
public:

	BVHNode() {
		Left = nullptr;
		Right = nullptr;
		
		triangles = vector<Triangle*>();
	}

	BVHNode(vector<Triangle*>& _triangles): triangles(_triangles) {
		Left = nullptr;
		Right = nullptr;
		
	}

	~BVHNode() {
		if (Left != nullptr) delete Left;
		if (Right != nullptr) delete Right;
	}

	float hit(const Ray& ray, vector<Triangle*>& hitTriangles) const;

	

	vector<Triangle*> triangles;

	Vec3 upper;
	Vec3 lower;

	BVHNode* Left;
	BVHNode* Right;
};

//Give -1 if you want random axis splitting
BVHNode* BuildBVH(vector<Triangle*>& triangles, Vec3 lower, Vec3 upper, int axis);




