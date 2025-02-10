#include "Sphere.h"

Sphere::Sphere() : pos(Vec3()), radius(1.0f)
{}

Sphere::Sphere(Vec3 _pos, float _radius) : pos(_pos), radius(_radius)
{}

Sphere::~Sphere() 
{}