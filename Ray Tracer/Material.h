#pragma once
#include "Vec3.h"


class Material
{

public:

	Material() 
	{
		color = Vec3(1, 1, 1);
		kd = 1.0f;

		s = 50.0f;
		ks = 0.4f;

		kr = 0.1f;
		
	}

	Vec3 color;
	float kd;

	float s;
	float ks;

	float kr;
};

