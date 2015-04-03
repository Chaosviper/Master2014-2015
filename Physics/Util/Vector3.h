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
	void SetX(float);
	void SetY(float);
	void SetZ(float);
	void Set(float, float, float);
	Vector3& operator=(const Vector3& other);
	Vector3& operator+=(const Vector3& other);
	Vector3& operator-=(const Vector3& other);
	Vector3& operator*=(float scalar);
	Vector3& operator/=(float scalar);
	const float& operator[](int i)const { return v[i]; };
	float& operator[](int i){ return v[i]; };
	float Modulus() const;
	float SqrMagnitude() const;
	void Normalize();

	
private:

	float v[3];
};

Vector3 operator+(const Vector3&,const Vector3&);
Vector3 operator-(const Vector3&, const Vector3&);
//Vector3 operator*(const Vector3&, const Vector3&);
Vector3 operator*(const Vector3&, float);
Vector3 operator/(const Vector3&, float);
namespace VectorOp
{
	float DistanceBetween(const Vector3& first, const Vector3& second);
	void VectorialProduct(const Vector3& first, const Vector3& second, Vector3& result);
	float DotProduct(const Vector3& first, const Vector3& second);
	
	static const Vector3 Zero;
}