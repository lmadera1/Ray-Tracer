#pragma once
#include <algorithm>
#include "Vec3.h"
#include "Ray.h"
#include "Material.h"


using namespace std;

class Object
{
public:

	virtual bool hit(const Ray& ray, Ray& normal) { return false; }

	Material material;

	
};

class Sphere : public Object 
{
public:
	Sphere() : Sphere(Vec3(), 1.0f) {}

	Sphere(Vec3 Center, float radius) : center(Center), radius(radius) { 
		material = Material();
	}

	bool hit(const Ray& ray, Ray& normal){
		Vec3 OC = ray.origin - center;
		double a = Vec3::dot(ray.direction, ray.direction);
		double b = 2 * Vec3::dot(ray.direction, OC);
		double c = Vec3::dot(OC, OC) - radius * radius;
		double rad = b * b - 4 * a * c;

		if (rad < 0) return false;

		double t;
		if (rad == 0) { t = -b / (2 * a); }

		else t = min(-b + sqrt(rad), -b - sqrt(rad)) / (2 * a);

		Vec3 Phit = ray.origin + ray.direction * t;

		Vec3 Nhit = Phit - center;

		normal.origin = Phit;

		normal.direction = Nhit.normalize();


		return true;
	}

	Vec3 center;
	float radius;
};


class Triangle : public Object 
{
	Triangle() : Triangle(Vec3(), Vec3(), Vec3()) {}

	Triangle(Vec3 a, Vec3 b, Vec3 c) : a(a), b(b), c(c) {}

	bool hit(const Ray& ray, Ray& normal) { return false; }

	Vec3 a;
	Vec3 b;
	Vec3 c;

};

