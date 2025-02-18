#pragma once
#include "Vec3.h"


class Material
{

public:

	Material() 
	{
		color = Vec3(1, 1, 1);
		kd = 1.0f;

		specularColor = Vec3(1, 1, 1);
		s = 50.0f;
		ks = 0.6f;
		
	}

	Vec3 color;
	float kd;

	Vec3 specularColor;
	float s;
	float ks;
};

