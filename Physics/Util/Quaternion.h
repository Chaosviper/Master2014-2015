#pragma once
#include "Matrix.h"

class Quaternion
{
public:
	Quaternion& operator+=(const Quaternion& other);
	Quaternion& operator-=(const Quaternion& other);
	Quaternion& operator*=(const Quaternion& other);
	Quaternion& operator/=(float scalar);
	Matrix<3, 3> ToMatrix() const;
	Quaternion();
	Quaternion(float, float, float, float);
	Quaternion(const Quaternion&);
	Quaternion& operator=(const Quaternion&);
	float Modulus() const;
	float GetValue(int i) const;
private:
	float _values[4];
};

void Normalize(Quaternion& quaternion);
Quaternion operator*(const Quaternion& first, const Quaternion& second);
Quaternion operator+(const Quaternion& first, const Quaternion& second);
Quaternion operator-(const Quaternion& first, const Quaternion& second);
