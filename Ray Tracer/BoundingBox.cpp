#include "BoundingBox.h"

float BoundingBox::hit(const Ray& ray) const {
	float tmin = (lower.x - ray.origin.x) / ray.direction.x;
	float tmax = (upper.x - ray.origin.x) / ray.direction.x;

	if (tmin > tmax) swap(tmin, tmax);

	float tymin = (lower.y - ray.origin.y) / ray.direction.y;
	float tymax = (upper.y - ray.origin.y) / ray.direction.y;

	if (tymin > tymax) swap(tymin, tymax);

	if (tmin > tymax || tymin > tmax) return -1;

	if (tymin > tmin) tmin = tymin;
	if (tymax < tmax) tmax = tymax;

	float tzmin = (lower.z - ray.origin.z) / ray.direction.z;
	float tzmax = (upper.z - ray.origin.z) / ray.direction.z;

	if (tzmin > tzmax) swap(tzmin, tzmax);

	if (tmin > tzmax || tzmin > tmax) return -1;

	if (tzmin > tmin) tmin = tzmin;
	if (tzmax < tmax) tmax = tzmax;

	return (tmin < 0 && tmax > 0) ? tmax : tmin;
}
