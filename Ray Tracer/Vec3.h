#pragma once
#include <cmath>
#include <numbers>
class Vec3
{
public:
	Vec3();
	Vec3(float x, float y, float z);
	
	Vec3 operator+(const Vec3& other) const;
	Vec3 operator-(const Vec3& other) const;

	Vec3 operator*(const double scalar) const;
	// Overloading float * Vec3 (friend function)
	friend Vec3 operator*(const double scalar, const Vec3& vec);

	Vec3 operator/(const double scalar) const;

	Vec3 operator/=(const double scalar);

	Vec3 operator*=(const double scalar);

	float X() const;

	float Y() const;

	float Z() const;

	double length() const;

	Vec3 normalize();

	static double dot(const Vec3& first, const Vec3& second);

	float x;
	float y;
	float z;
};