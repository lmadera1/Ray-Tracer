#pragma once
#include "Vec3.h";

class Ray
{
public:
	Ray();

	Ray(Vec3 pos, Vec3 dir);	

	~Ray();
	
	Vec3 origin;
	Vec3 direction;
};

