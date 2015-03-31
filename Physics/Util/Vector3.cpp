#include "Vector3.h"
const Vector3 Vector3::_zero = Vector3(0, 0, 0);

Vector3 operator+(const Vector3& first, const Vector3& second)
{
	Vector3 result(first);
	return result += second;
}
Vector3 operator*(const Vector3& vector,float scalar)
{
	return Vector3(vector.getX() * scalar, vector.getY()* scalar, vector.getZ() * scalar);
}

Vector3 operator/(const Vector3& vector, float scalar)
{
	return Vector3(vector.getX() / scalar, vector.getY() / scalar, vector.getZ() / scalar);
}

Vector3 operator-(const Vector3& first, const Vector3& second)
{
	Vector3 result(first);
	return result -= second;
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

void Vector3::SetX(float x)
{
	v[0] = x;
}
void Vector3::SetY(float y)
{
	v[1] = y;
}
void Vector3::SetZ(float z)
{
	v[0] = z;
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
Vector3& Vector3::operator/=(float scalar)
{
	v[0] /= scalar;
	v[1] /= scalar;
	v[2] /= scalar;
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

void Normalize(Vector3& vector)
{
	float mod = vector.Modulus();
	if (mod > 0.000001f) {
		vector /= mod;
	}
}

float Vector3::Modulus() const
{
	return(sqrt((v[0] * v[0]) + (v[1] * v[1]) + (v[2] * v[2])));
};

void VectorialProduct(const Vector3& first, const Vector3& second, Vector3& result)
{
	//float X = (p3[1] * s3[2]) - (p3[2] * s3[1]);
	//float Y = (p3[2] * s3[0]) - (p3[0] * s3[2]);
	//float Z = (p3[0] * s3[1]) - (p3[1] * s3[0]);
	
	float X = (first.getY() * second.getZ()) - (first.getZ() * second.getY());
	float Y = (first.getZ() * second.getX()) - (first.getX() * second.getZ());
	float Z = (first.getX() * second.getY()) - (first.getY() * second.getX());
	result.SetX(X);
	result.SetY(Y);
	result.SetZ(Z);
}

float DotProduct(const Vector3& first, const Vector3& second)
{
	return((first.getX() * second.getX()) + (first.getY() * second.getY()) + (first.getZ() * second.getZ()));
}

const float* Vector3::GetData() const 
{
	return v;
}