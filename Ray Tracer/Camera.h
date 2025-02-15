#pragma once
#include "Vec3.h"
class Camera
{
public:

	Camera() : Camera(Vec3(), Vec3(0.0f, 0.0f, -1.0f))
	{}

	Camera(Vec3 pos, Vec3 dir)
		: Camera(pos, dir, 0.0156f, 1.0f, 0.01f)
	{}

	Camera(Vec3 pos, Vec3 dir, float sensor_width, float aspect_ratio, float focal_length);

	void SetAspectRatio(float aspect_ratio);

	Vec3 Forward() const;
	Vec3 Up() const;
	Vec3 Right() const;

	Vec3 UpperLeft() const;

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
	Vec3 upper_left;
	float sensor_width;
	float sensor_height;
};

