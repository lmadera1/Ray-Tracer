#pragma once
#include "Vec3.h"
class Camera
{
public:

	Camera();
	~Camera();
	Camera(int width, int height);
	Camera(Vec3 pos, Vec3 dir, int width, int height, float focal_length);

	Vec3 pos;
	Vec3 dir;
	Vec3 horizontal;
	Vec3 vertical;
	float focal_length;



};

