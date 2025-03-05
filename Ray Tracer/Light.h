#pragma once
#include "Vec3.h"
class Light
{
public:
	Vec3 color;
};

class Sun : public Light 
{
public:
	Sun() : Sun(Vec3(0, -1.0f, 0)) {

	}

	Sun(Vec3 dir) {
		color = Vec3(1, 1, 1);
		direction = dir.normalize();
	}


	Vec3 direction;
};