#pragma once
#include "Vec3.h";

class Ray
{
public:
	Ray();

	Ray(Vec3 pos, Vec3 dir);

	Vec3 Direction() const;
	Vec3 Origin() const;

	~Ray();
private:
	
	Vec3 origin;
	Vec3 direction;
};

