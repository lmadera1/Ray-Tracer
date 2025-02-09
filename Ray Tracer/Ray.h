#pragma once
#include "Vec3.h";
class Ray
{
	Ray();
	Ray(Vec3 pos, Vec3 dir);
	
	Vec3 pos;
	Vec3 dir;
};

