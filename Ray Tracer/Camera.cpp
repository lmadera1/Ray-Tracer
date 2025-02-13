#include "Camera.h"


Camera::Camera(Vec3 pos, Vec3 dir, float _sensor_width, float aspect_ratio, float focal_length)
	: origin(pos), forward(dir), sensor_width(_sensor_width),focal_length(focal_length)
{
	right = Vec3(1, 0, 0);
	up = Vec3(0, 1, 0);
	sensor_height = sensor_width / aspect_ratio;
	lower_corner = origin + forward * focal_length - right * sensor_width / 2 - up * sensor_height / 2;
}

Camera::~Camera()
{}

void Camera::SetAspectRatio(float aspect_ratio)
{
	sensor_height = sensor_width / aspect_ratio;
	lower_corner = origin + forward * focal_length - right * sensor_width / 2 - up * sensor_height / 2;
}

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
	


