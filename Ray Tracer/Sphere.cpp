#include "Sphere.h"

Sphere::Sphere() : Sphere::Sphere(Vec3(), 1.0f)
{}

Sphere::Sphere(Vec3 _pos, double _radius) : center(_pos), radius(_radius), color(Vec3(255, 255, 255))
{}

Vec3 Sphere::Center() const 
{
	return center;
}

double Sphere::Radius() const 
{
	return radius;
}

Vec3 Sphere::Color() const
{
	return color;
}

void Sphere::SetColor(Vec3 _color) 
{
	color = _color;
}

Sphere::~Sphere() 
{}