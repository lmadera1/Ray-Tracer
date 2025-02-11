#pragma once
#include "Vec3.h"
class Camera
{
public:

	Camera() : Camera(400, 400)	
	{}

	Camera(int width, int height)
		: Camera(Vec3(), Vec3(0, 0, -1), width, height, 1.0f)
	{}

	Camera(Vec3 pos, Vec3 dir, int width, int height, float focal_length)
		: origin(pos), forward(dir), focal_length(focal_length)
	{
		right = Vec3(1, 0, 0);
		up = Vec3(0, 1, 0);
		lower_corner = origin + forward * focal_length - right * width / 2 - up * height / 2;
	}

	Vec3 Forward() const;
	Vec3 Up() const;
	Vec3 Right() const;

	Vec3 LowerCorner() const;

	Vec3 Origin() const;

	~Camera();

	

private:
	Vec3 origin;
	Vec3 forward;
	Vec3 right;
	Vec3 up;
	float focal_length;
	Vec3 lower_corner;
};

