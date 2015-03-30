#pragma once
#include <math.h>
class Vector3
{
public:
	Vector3();
	Vector3(float x, float y, float z);
	Vector3(const Vector3& other);

	float getX() const;
	float getY() const;
	float getZ() const;

	Vector3& operator=(const Vector3& other);
	Vector3& operator+=(const Vector3& other);
	Vector3& operator-=(const Vector3& other);
	Vector3& operator*=(float scalar);

	static const Vector3& zeroes();
	static float DistanceBetween(const Vector3& first, const Vector3& second);
	
private:
	//MAH
	static const Vector3 _zero;
	float v[3];
};

Vector3& operator+(const Vector3&,const Vector3&);
Vector3& operator-(const Vector3&, const Vector3&);
Vector3& operator*(const Vector3&, const Vector3&);
Vector3& operator*(const Vector3&, float);
Vector3& operator/(const Vector3&, float);
