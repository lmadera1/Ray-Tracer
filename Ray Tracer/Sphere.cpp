#include "Sphere.h"

Sphere::Sphere() : center(Vec3()), radius(1.0f)
{}

Sphere::Sphere(Vec3 _pos, double _radius) : center(_pos), radius(_radius)
{}

Vec3 Sphere::Center() const 
{
	return center;
}

double Sphere::Radius() const 
{
	return radius;
}

Sphere::~Sphere() 
{}