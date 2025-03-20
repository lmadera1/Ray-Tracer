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

	Vec3 lower() const {
		return Vec3(
			std::min(A.x, std::min(B.x, C.x)),
			std::min(A.y, std::min(B.y, C.y)),
			std::min(A.z, std::min(B.z, C.z))
		);
	}

	Vec3 upper() const {
		return Vec3(
			std::max(A.x, std::max(B.x, C.x)),
			std::max(A.y, std::max(B.y, C.y)),
			std::max(A.z, std::max(B.z, C.z))
		);
	}

	Vec3 centroid() const {
		return (A + B + C) / 3;
	}

	Vec3 A;
	Vec3 B;
	Vec3 C;

};

