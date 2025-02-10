#include "Ray.h"

Ray::Ray() : pos(Vec3()), dir(Vec3(0, 0, 1))
{}

Ray::Ray(Vec3 pos, Vec3 dir) : pos(pos), dir(dir)
{}

Ray::~Ray() 
{}