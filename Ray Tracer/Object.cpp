#include "Object.h"

bool Sphere::hit(const Ray& ray, Ray& normal) const {
	Vec3 OC = ray.origin - center;
	double a = dot(ray.direction, ray.direction);
	double b = 2 * dot(ray.direction, OC);
	double c = dot(OC, OC) - radius * radius;
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

bool Triangle::hit(const Ray& ray, Ray& normal) const {
 
	Vec3 N = cross(B - A, C - A).normalize();

	float t = dot(N, A - ray.origin) / dot(N, ray.direction);

	if (t <= 0) return false;

	Vec3 P = ray.origin + t * ray.direction;

	float TotalArea = area(B - A, C - A);

	float u = area(B - P, C - P) / TotalArea;

	float v = area(A - P, C - P) / TotalArea;

	float w = area(A - P, B - P) / TotalArea;

	if (u < 0 || v < 0 || w < 0 || u + v + w > 1.001 || u + v + w < 0.999) return false;

	normal.origin = P;
	normal.direction = N;

	return true;
}
