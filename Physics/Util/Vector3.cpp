#include "Vector3.h"

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