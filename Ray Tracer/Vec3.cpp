#include "Vec3.h"

Vec3::Vec3() : x(0.0f), y(0.0f), z(0.0f) 
{}

Vec3::Vec3(float _x, float _y, float _z) : x(_x), y(_y), z(_z) 
{}

Vec3 Vec3::operator+(const Vec3& other) const
{
	return Vec3(x + other.x, y + other.y, z + other.z);
}

Vec3 Vec3::operator-(const Vec3& other) const 
{
	return Vec3(x - other.x, y - other.y, z - other.z);
}

Vec3 Vec3::operator*(const double scalar) const 
{
	return Vec3(x * scalar, y * scalar, z * scalar);
}

// Overloading float * Vec3 (friend function)
Vec3 operator*(const double scalar, const Vec3& other) 
{
	return other * scalar;
}

Vec3 Vec3::operator/(const double scalar) const
{
	return Vec3(x / scalar, y / scalar, z / scalar);
}

Vec3 Vec3::operator/=(const double scalar) 
{
	x /= scalar;
	y /= scalar;
	z /= scalar;
	return *this;
}

float Vec3::X() const
{
	return x;
}

float Vec3::Y() const
{
	return y;
}

float Vec3::Z() const
{
	return z;
}


double Vec3::length() const 
{
	return sqrt(x*x + y*y + z*z);
}


Vec3 Vec3::normalize() 
{
	return Vec3(*this /= this->length());
}

double Vec3::dot(const Vec3& first, const Vec3& second) 
{
	return first.X() * second.X() + first.Y() * second.Y() + first.Z() * second.Z();
}