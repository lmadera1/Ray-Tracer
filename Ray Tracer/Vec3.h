#pragma once
#include <cmath>

class Vec3 
{
public:

	Vec3() : Vec3(0.0f, 0.0f, 0.0f) {}

	Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

	Vec3 operator+(const Vec3& other) const {
		return Vec3(x + other.x, y + other.y, z + other.z);
	}

	Vec3 operator-(const Vec3& other) const {
		return Vec3(x - other.x, y - other.y, z - other.z);
	}

	Vec3 operator*(const float scalar) const {
		return Vec3(x * scalar, y * scalar, z * scalar);
	}

	Vec3 operator/(const float scalar) const {
		return Vec3(x / scalar, y / scalar, z / scalar);
	}

	// Overloading float * Vec3 (friend function)
	friend Vec3 operator*(const double scalar, const Vec3& other)
	{
		return other * scalar;
	}

	void operator*=(const float scalar) {
		*this = *this * scalar;
	}

	void operator/=(const float scalar) {
		*this = *this / scalar;
	}

	Vec3 normalize() const {
		return Vec3(*this) / this->length();
	}

	float length() const {
		return sqrt(x * x + y * y + z * z);
	}


	float x, y, z;

};


float dot(const Vec3& first, const Vec3& second);

Vec3 cross(const Vec3& first, const Vec3& second);


class Ray 
{
public:
	Ray() : origin(Vec3()), direction(Vec3()) {}

	Ray(Vec3& position, Vec3& magnitude) 
		: origin(position), direction(magnitude) 
	{}


	Vec3 origin;
	Vec3 direction;

};