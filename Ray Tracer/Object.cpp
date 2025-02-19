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

	Vec3 PA = P - A;

	Vec3 BA = B - A;

	Vec3 CA = C - A;

	float u = dot(PA, BA) / dot(BA, BA);

	float v = dot(PA, CA) / dot(CA, CA);

	if (u < 0 || v < 0 || u + v > 1) return false;


	//|a||b|cos(theta) = dot(a, b)



	// proj = |a|cos(theta) * b.normalize()  = comp * b.normalize()
	//comp = |a|cos(theta) = dot(a, b) / |b|

	// proj = u * b
	// u = comp / |b| = dot(a, b) / |b|^2 = dot(a, b) / dot(b, b)
	// a = 

	normal.origin = P;
	normal.direction = N;

	return true;
}
