#include "Quaternion.h"
#include <math.h>
Quaternion::Quaternion()
{
	_values[0] = 0;
	_values[1] = 0;
	_values[2] = 0;
	_values[3] = 0;
}

Quaternion::Quaternion(float a, float i, float j, float k)
{
	_values[0] = a;
	_values[1] = i;
	_values[2] = j;
	_values[3] = k;
};

Quaternion::Quaternion(const Quaternion& other)
{
	_values[0] = other.GetValue(0);
	_values[1] = other.GetValue(1);
	_values[2] = other.GetValue(2);
	_values[3] = other.GetValue(3);

};
Quaternion& Quaternion::operator = (const Quaternion& other)
{
	if (this != &other)
	{	
		_values[0] = other.GetValue(0);
		_values[1] = other.GetValue(1);
		_values[2] = other.GetValue(2);
		_values[3] = other.GetValue(3);
	}
	return *this;
};

Quaternion operator+(const Quaternion& first, const Quaternion& second)
{
	Quaternion result(first);
	result += second;
	return result;
};
Quaternion operator-(const Quaternion& first, const Quaternion& second)
{
	Quaternion result(first);
	result -= second;
	return result;
};
Quaternion& Quaternion::operator+=(const Quaternion& other)
{
	_values[0] += other.GetValue(0);
	_values[1] += other.GetValue(1);
	_values[2] += other.GetValue(2);
	_values[3] += other.GetValue(3);
	return *this;
};
Quaternion& Quaternion::operator-=(const Quaternion& other)
{
	_values[0] -= other.GetValue(0);
	_values[1] -= other.GetValue(1);
	_values[2] -= other.GetValue(2);
	_values[3] -= other.GetValue(3);
	return *this;
};
Quaternion& Quaternion::operator/=(float scalar)
{
	_values[0] /= scalar;
	_values[1] /= scalar;
	_values[2] /= scalar;
	_values[3] /= scalar;
	return *this;
};

float Quaternion::GetValue(int i) const
{
	return _values[i];
};

Quaternion operator*(const Quaternion& first, const Quaternion& second)
{
	Quaternion result(first);
	result *= second;
	return result;
};

Quaternion& Quaternion::operator*=(const Quaternion& other)
{
	//	float S = p4[0] * s4[0] - p4[1] * s4[1] - p4[2] * s4[2] - p4[3] * s4[3];
	_values[0] = GetValue(0) * other.GetValue(0) - GetValue(1) * other.GetValue(1) - GetValue(2) * other.GetValue(2) - GetValue(3) * other.GetValue(3);
	//	float X = p4[0] * s4[1] + p4[1] * s4[0] + p4[2] * s4[3] - p4[3] * s4[2]
	_values[1] = GetValue(0) * other.GetValue(1) + GetValue(1) * other.GetValue(0) + GetValue(2) * other.GetValue(3) - GetValue(3) * other.GetValue(2);
	//	float Y = p4[0] * s4[2] - p4[1] * s4[3] + p4[2] * s4[0] + p4[3] * s4[1];
	_values[2] = GetValue(0) * other.GetValue(2) - GetValue(1) * other.GetValue(3) + GetValue(2) * other.GetValue(0) + GetValue(3) * other.GetValue(1);
	//	float Z = p4[0] * s4[3] + p4[1] * s4[2] - p4[2] * s4[1] + p4[3] * s4[0];
	_values[3] = GetValue(0) * other.GetValue(3) + GetValue(1) * other.GetValue(2) - GetValue(2) * other.GetValue(1) + GetValue(3) * other.GetValue(0);
	return *this;
};

float Quaternion::Modulus() const
{
	return(sqrt((GetValue(0) * GetValue(0)) + (GetValue(1) * GetValue(1)) + (GetValue(2) * GetValue(2)) + (GetValue(3) * GetValue(3))));
};

void Normalize(Quaternion& quaternion)
{
	float a = quaternion.Modulus();
	if (a > 0.000001f) {
		quaternion /= a;
	}
};

Matrix<3, 3> Quaternion::ToMatrix() const
{
	float X2 = GetValue(1) * GetValue(1);
	float Y2 = GetValue(2) * GetValue(2);
	float Z2 = GetValue(3) * GetValue(3);
	float XY = GetValue(1) * GetValue(2);
	float XZ = GetValue(1) * GetValue(3);
	float YZ = GetValue(2) * GetValue(3);
	float SX = GetValue(0) * GetValue(1);
	float SY = GetValue(0) * GetValue(2);
	float SZ = GetValue(0) * GetValue(3);
	Matrix<3, 3> result;

	result.SetElementAt(0, 1.0f - 2.0f * (Y2 + Z2));
	result.SetElementAt(1, 2.0f * (XY + SZ));
	result.SetElementAt(2, 2.0f * (XZ - SY));
	result.SetElementAt(3, 2.0f * (XY - SZ));
	result.SetElementAt(4, 1.0f - 2.0f * (Z2 + X2));
	result.SetElementAt(5, 2.0f * (YZ + SX));
	result.SetElementAt(6, 2.0f * (XZ + SY));
	result.SetElementAt(7, 2.0f * (YZ - SX));
	result.SetElementAt(8, 1.0f - 2.0f * (X2 + Y2));
	return result;
};