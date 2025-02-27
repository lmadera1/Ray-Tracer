#include "Object.h"

float Sphere::hit(const Ray& ray, Ray& normal) const {
	Vec3 OC = ray.origin - center;
	double a = dot(ray.direction, ray.direction);
	double b = 2 * dot(ray.direction, OC);
	double c = dot(OC, OC) - radius * radius;
	double rad = b * b - 4 * a * c;

	if (rad < 0) return false;

	double t;
	if (rad == 0) { t = -b / (2 * a); }

	else t = min(-b + sqrt(rad), -b - sqrt(rad)) / (2 * a);

	if (t <= 0) return false;

	Vec3 Phit = ray.origin + ray.direction * t;

	Vec3 Nhit = Phit - center;

	normal.origin = Phit;

	normal.direction = Nhit.normalize();


	return t;
}


float Triangle::hit(const Ray& ray, Ray& normal) const {

	
	Vec3 N = cross(B - A, C - A).normalize();

	//Ray parallel to triangle
	if (dot(N, ray.direction) == 0) return false;

	float t = dot(N, A - ray.origin) / dot(N, ray.direction);

	if (t <= 0) return false;

	Vec3 P = ray.origin + t * ray.direction;

	float u = dot(N, cross(B - A, P - A));
	float v = dot(N, cross(C - B, P - B));
	float w = dot(N, cross(A - C, P - C));

	if (u < 0 || v < 0 || w < 0) return false;

	normal.origin = P;
	normal.direction = -1 * N;

	return t;

	
}

void Object::SetColor(const Vec3& color) {

	if (color.x < 0 || color.y < 0 || color.z < 0) return;
	if (color.x > 255 || color.y > 255 || color.z > 255) return;

	material.color = color / 255;
}
