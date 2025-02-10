#pragma once
#include "Vec3.h"
class Sphere
{
public:
	Sphere();
	Sphere(Vec3 pos, float radius);
	~Sphere();
private:
	Vec3 pos;
	float radius;
};

