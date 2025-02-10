#pragma once
#include "Vec3.h";

class Ray
{
public:
	Ray();

	Ray(Vec3 pos, Vec3 dir);

	~Ray();
private:
	
	Vec3 pos;
	Vec3 dir;
};

