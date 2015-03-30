#include "Vector3.h"
const Vector3 Vector3::_zero = Vector3(0, 0, 0);

Vector3& operator+(const Vector3& first, const Vector3& second)
{
	Vector3 result(first);
	return result += second;
}
Vector3& operator*(const Vector3& vector,float scalar)
{
	return Vector3(vector.getX() * scalar, vector.getY()* scalar, vector.getZ() * scalar);
}

Vector3& operator/(const Vector3& vector, float scalar)
{
	return Vector3(vector.getX() / scalar, vector.getY() / scalar, vector.getZ() / scalar);
}

Vector3& operator-(const Vector3& first, const Vector3& second)
{
	Vector3 result(first);
	return result -= second;
}
Vector3& operator*(const Vector3& first, const Vector3& second)
{
	Vector3 result(first);
	//TO DO
	return result;
}

float Vector3::getX() const
{
	return v[0];
}
float Vector3::getY() const
{
	return v[1];
}
float Vector3::getZ() const
{
	return v[2];
}
Vector3::Vector3(float x, float y, float z)
{
	v[0] = x;
	v[1] = y;
	v[2] = z;
}
Vector3::Vector3()
{
	v[0] = 0;
	v[1] = 0;
	v[2] = 0;

}
Vector3::Vector3(const Vector3& other)
{
	v[0] = other.getX();
	v[1] = other.getY();
	v[2] = other.getZ();
}
Vector3& Vector3::operator=(const Vector3& other)
{
	if (this != &other)
	{
		v[0] = other.getX();
		v[1] = other.getY();
		v[2] = other.getZ();
	}
	return *this;
}
Vector3& Vector3::operator+=(const Vector3& other)
{
	v[0] += other.getX();
	v[1] += other.getY();
	v[2] += other.getZ();
	return *this;
}

Vector3& Vector3::operator-=(const Vector3& other)
{
	v[0] -= other.getX();
	v[1] -= other.getY();
	v[2] -= other.getZ();
	return *this;
}

Vector3& Vector3::operator*=(float scalar)
{
	v[0] *= scalar;
	v[1] *= scalar;
	v[2] *= scalar;
	return *this;
}

const Vector3& Vector3::zeroes()
{
	return _zero;
}

float Vector3::DistanceBetween(const Vector3& first, const Vector3& second)
{
	return sqrt(pow(first.getX() + second.getX(), 2) + pow(first.getY() + second.getY(), 2) + pow(first.getZ() + second.getZ(), 2));
};
