#include "Vec3.h"
float dot(const Vec3& first, const Vec3& second) {
	return first.x * second.x + first.y * second.y + first.z * second.z;
}

Vec3 cross(const Vec3& first, const Vec3& second) 
{
	float x = first.y * second.z - first.z * second.y;
	float y = first.x * second.z - first.z * second.x;
	float z = first.x * second.y - first.y * second.x;

	return Vec3(x, y, z);
}