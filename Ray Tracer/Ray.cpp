#include "Ray.h"

Ray::Ray() 
{
	pos = Vec3(0, 0, 0);
	dir = Vec3(0, 0, 0);
}
Ray::Ray(Vec3 pos, Vec3 dir) 
{
	this->pos = pos;
	this->dir = dir;
}
