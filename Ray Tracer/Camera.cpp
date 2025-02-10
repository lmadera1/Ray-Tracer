#include "Camera.h"


Camera::Camera() 
{
	pos = Vec3(0, 0, 0);
	dir = Vec3(0, 0, -1);
	focal_length = 1.0f;
	int width = 400;
	int height = 400;
	horizontal = Vec3(width, 0, 0);
	vertical = Vec3(0, height, 0);
}

Camera::Camera(int width, int height) 
{
	pos = Vec3(0, 0, 0);
	dir = Vec3(0, 0, -1);
	focal_length = 1.0f;
	horizontal = Vec3(width, 0, 0);
	vertical = Vec3(0, height, 0);

}

Camera::Camera(Vec3 _pos, Vec3 _dir, int width, int height, float _focal_length) 
{
	pos = _pos;
	dir = _dir;
	focal_length = _focal_length;
	horizontal = Vec3(width, 0, 0);
	vertical = Vec3(0, height, 0);
}

Camera::~Camera() 
{

}
