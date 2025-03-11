#pragma once
#include <algorithm>
#include "Vec3.h"
#include "Material.h"


using namespace std;

class Triangle
{
public:
	Triangle() : Triangle(Vec3(0, 0, -1), Vec3(1, 0, -1), Vec3(0, 1, -1)) {}

	Triangle(Vec3 a, Vec3 b, Vec3 c) : A(a), B(b), C(c) {}

	float hit(const Ray& ray, Ray& normal) const;

	void SetColor(const Vec3& color);

	Vec3 A;
	Vec3 B;
	Vec3 C;

	Material material;

};

