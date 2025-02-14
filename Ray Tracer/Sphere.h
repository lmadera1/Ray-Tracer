#pragma once
#include "Vec3.h"
class Sphere
{
public:
	Sphere();
	Sphere(Vec3 pos, double radius);
	Vec3 Center() const;
	double Radius() const;
	Vec3 Color() const;
	void SetColor(Vec3 color);
	~Sphere();
private:
	Vec3 center;
	double radius;
	Vec3 color;
};

