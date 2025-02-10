#include "Sphere.h"

Sphere::Sphere() 
{
	radius = 1.0f;
	pos = Vec3();
}

Sphere::Sphere(Vec3 _pos, float _radius) 
{
	pos = _pos;
	radius = _radius;
}

Sphere::~Sphere() 
{

}