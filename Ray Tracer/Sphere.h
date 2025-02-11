#pragma once
#include "Vec3.h"
class Sphere
{
public:
	Sphere();
	Sphere(Vec3 pos, double radius);
	Vec3 Center() const;
	double Radius() const;
	~Sphere();
private:
	Vec3 center;
	double radius;
};

