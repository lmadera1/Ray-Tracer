#include "Vec3.h"
float dot(const Vec3& first, const Vec3& second) {
	return first.x * second.x + first.y * second.y + first.z * second.z;
}

Vec3 cross(const Vec3& first, const Vec3& second) 
{
	float x = first.y * second.z - first.z * second.y;
	float y = first.z * second.x - first.x * second.z;
	float z = first.x * second.y - first.y * second.x;

	return Vec3(x, y, z);
}

Vec3 FromPolar(const float radius, const float theta, const float phi) {

	float temp = sin(theta) * cos(phi);
	return Vec3(
		radius * sin(theta) * cos(phi),
		radius * cos(theta),
		radius * sin(theta) * sin(phi)
	);
}