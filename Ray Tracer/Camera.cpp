#include "Camera.h"


Camera::Camera(Vec3 pos, Vec3 dir, float _sensor_width, float aspect_ratio, float focal_length)
	: origin(pos), forward(dir), sensor_width(_sensor_width),focal_length(focal_length)
{
	right = Vec3(1, 0, 0);
	up = Vec3(0, 1, 0);
	SetAspectRatio(aspect_ratio);
}

Camera::~Camera()
{}

void Camera::SetAspectRatio(float aspect_ratio)
{
	sensor_height = sensor_width / aspect_ratio;
	upper_left = origin + forward * focal_length - right * sensor_width / 2 + up * sensor_height / 2;
}

Vec3 Camera::UpperLeft() const{
	return Vec3(upper_left);
}

float Camera::SensorW() const 
{
	return sensor_width;
}

float Camera::SensorH() const 
{
	return sensor_height;
}
	


