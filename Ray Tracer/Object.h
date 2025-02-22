#pragma once
#include <algorithm>
#include "Vec3.h"
#include "Material.h"


using namespace std;

class Object
{
public:

	virtual bool hit(const Ray& ray, Ray& normal) const {
		return false; 
	}

	Material material;

	
};

class Sphere : public Object 
{
public:
	Sphere() : Sphere(Vec3(), 1.0f) {}

	Sphere(Vec3 Center, float radius) : center(Center), radius(radius) { 
		material = Material();
	}

	bool hit(const Ray& ray, Ray& normal) const;

	float radius;
	Vec3 center;
	
};


class Triangle : public Object 
{
public:
	Triangle() : Triangle(Vec3(0, 0, -1), Vec3(1, 0, -1), Vec3(0, 1, -1)) {}

	Triangle(Vec3 a, Vec3 b, Vec3 c) : A(a), B(b), C(c) {}

	bool hit(const Ray& ray, Ray& normal) const;

	Vec3 A;
	Vec3 B;
	Vec3 C;

};

