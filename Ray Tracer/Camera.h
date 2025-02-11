#pragma once
#include "Vec3.h"
class Camera
{
public:

	Camera() : Camera(Vec3(), Vec3(0.0f, 0.0f, -1.0f))
	{}

	Camera(Vec3 pos, Vec3 dir)
		: Camera(pos, dir, 0.0156f, 0.0156f, 0.01f)
	{}

	Camera(Vec3 pos, Vec3 dir, float width, float height, float focal_length)
		: origin(pos), forward(dir), focal_length(focal_length)
	{
		right = Vec3(1, 0, 0);
		up = Vec3(0, 1, 0);
		sensor_width = width;
		sensor_height = height;
		lower_corner = origin + forward * focal_length - right * sensor_width / 2 - up * sensor_height / 2;
	}

	Vec3 Forward() const;
	Vec3 Up() const;
	Vec3 Right() const;

	Vec3 LowerCorner() const;

	Vec3 Origin() const;

	float SensorW() const;

	float SensorH() const;

	~Camera();

	

private:
	Vec3 origin;
	Vec3 forward;
	Vec3 right;
	Vec3 up;
	float focal_length;
	Vec3 lower_corner;
	float sensor_width;
	float sensor_height;
};

