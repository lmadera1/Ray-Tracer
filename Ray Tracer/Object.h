#pragma once

#include "Triangle.h";
#include <vector>;
#include "BoundingBox.h";

class Object
{
public:

	Object() {}

	Object(vector<Triangle*>& _triangles, Material& _material, BoundingBox& _bb) : 
		triangles(_triangles), material(_material), bb(_bb) {}

	Material material;

	vector<Triangle*> triangles;

	BoundingBox bb;

};

