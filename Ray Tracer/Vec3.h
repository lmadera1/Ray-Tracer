#pragma once
class Vec3
{
public:
	Vec3();
	Vec3(float x, float y, float z);
	~Vec3();

	Vec3 operator+(const Vec3& other) const;
	Vec3 operator-(const Vec3& other) const;
	Vec3 operator*(const Vec3& other) const;
	Vec3 operator/(const Vec3& other) const;

	Vec3 operator*(float scalar) const;
	Vec3 operator/(float scalar) const;

	Vec3& operator+=(const Vec3& other);
	Vec3& operator-=(const Vec3& other);
	Vec3& operator*=(const Vec3& other);
	Vec3& operator/=(const Vec3& other);

	Vec3& operator*=(float scalar);
	Vec3& operator/=(float scalar);

	float dot(const Vec3& other) const;
	Vec3 cross(const Vec3& other) const;
	float length() const;
	Vec3 normalize() const;

	float x, y, z;
};

