#pragma once
#include "Vec3.h"
class Light
{
};

class Sun : public Light 
{
public:
	Sun() : Sun(Vec3(0, -1.0f, 0)) {

	}

	Sun(Vec3 dir) {

		direction = dir.normalize();
	}


	Vec3 direction;
};