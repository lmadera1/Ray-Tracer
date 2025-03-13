#include "Triangle.h"

float Triangle::hit(const Ray& ray, Ray& hitNormal) const {
	Vec3 edge1 = B - A;
	Vec3 edge2 = C - A;

	Vec3 normal = cross(edge1, edge2).normalize();

	Vec3 h = cross(ray.direction, edge2);

	float a = dot(edge1, h);

	if (abs(a) < numeric_limits<float>::epsilon()) return -1;

	float f = 1 / a;

	Vec3 s = ray.origin - A;

	float u = dot(s, h) * f;

	if (u < 0 || u > 1) return -1;

	Vec3 q = cross(s, edge1);

	float v = dot(ray.direction, q) * f;

	if (v < 0 || v > 1 || u + v > 1) return -1;


	float t = dot(edge2, q) * f;

	if (t <= numeric_limits<float>::epsilon()) return -1;

	hitNormal.origin = ray.origin + t * ray.direction;
	hitNormal.direction = normal;
	return t;

}
