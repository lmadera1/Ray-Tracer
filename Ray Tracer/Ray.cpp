#include "Ray.h"

Ray::Ray() : origin(Vec3()), direction(Vec3(0, 0, 1))
{}

Ray::Ray(Vec3 pos, Vec3 dir) : origin(pos), direction(dir)
{}

Vec3 Ray::Direction() const 
{
	return Vec3(direction);
}

Vec3 Ray::Origin() const 
{
	return Vec3(origin);
}

Ray::~Ray() 
{}