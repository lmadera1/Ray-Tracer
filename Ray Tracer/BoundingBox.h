#pragma once
#include "Vec3.h"
#include <algorithm>

using namespace std;

class BoundingBox
{
public:

	BoundingBox() : upper(Vec3()), lower(Vec3()) {}

	BoundingBox(const Vec3& upper, const Vec3& lower) : upper(upper), lower(lower) {}

	float hit(const Ray& ray) const;

	Vec3 upper;
	Vec3 lower;
};

