#pragma once
#include <math.h>
class Vector3
{
public:
	float getX() const
	{	
		return v[0];
	}
	float getY() const
	{
		return v[1];
	}
	float getZ() const
	{
		return v[2];
	}
	Vector3(float x, float y, float z)
	{
		v[0] = x;
		v[1] = y;
		v[2] = z;
	}
	Vector3()
	{
		v[0] = 0;
		v[1] = 0;
		v[2] = 0;

	}
	Vector3(const Vector3& other)
	{
		v[0] = other.getX();
		v[1] = other.getY();
		v[2] = other.getZ();
	}
	Vector3& operator=(const Vector3& other)
	{
		if (this != &other)
		{
			v[0] = other.getX();
			v[1] = other.getY();
			v[2] = other.getZ();
		}
		return *this;
	}
	Vector3& operator+=(const Vector3& other)
	{
		v[0] += other.getX();
		v[1] += other.getY();
		v[2] += other.getZ();
		return *this;
	}



	static float DistanceBetween(const Vector3& first, const Vector3& second)
	{
		return sqrt(pow(first.getX() + second.getX(), 2) + pow(first.getY() + second.getY(), 2) + pow(first.getZ() + second.getZ(), 2));
	};

private:
	float v[3];
};

Vector3& operator+(const Vector3&,const Vector3&);
Vector3& operator*(const Vector3&, float);
Vector3& operator/(const Vector3&, float);
