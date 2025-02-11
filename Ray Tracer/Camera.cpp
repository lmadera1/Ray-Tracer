#include "Camera.h"


Camera::~Camera()
{}

Vec3 Camera::Up() const
{
	return Vec3(up);
}

Vec3 Camera::Right() const
{
	return Vec3(right);
}

Vec3 Camera::Forward() const
{
	return Vec3(forward);
}

Vec3 Camera::LowerCorner() const{
	return Vec3(lower_corner);
}

Vec3 Camera::Origin() const
{
	return origin;
}

float Camera::SensorW() const 
{
	return sensor_width;
}

float Camera::SensorH() const 
{
	return sensor_height;
}
	


