#include "Matrix.h"
#include <iostream>
namespace MatrixOp{



template<int Row, int Col>
void Rotate(const Matrix<Row, Col>& Matrix, const float* vector, float * result)
{
	for (int i = 0; i < Row; ++i)
	{
		result[i] = 0;
		for (int j = 0; j < Col; ++j)
		{
			result[i] += Matrix.GetElementAt(i, j) * vector[j];
		}
	}
};

template<RotateTo To>
void Rotate(const Matrix<3, 3>& Matrix, const Vector3& vector, Vector3& result);

template<>
void Rotate<ToObjSpace>(const Matrix<3, 3>& Matrix, const Vector3& vector, Vector3& result)
{
	float x = Matrix.GetElementAt(0) * vector.getX() + Matrix.GetElementAt(1) * vector.getY() + Matrix.GetElementAt(2) * vector.getZ();
	float y = Matrix.GetElementAt(3) * vector.getX() + Matrix.GetElementAt(4) * vector.getY() + Matrix.GetElementAt(5) * vector.getZ();
	float z = Matrix.GetElementAt(6) * vector.getX() + Matrix.GetElementAt(7) * vector.getY() + Matrix.GetElementAt(8) * vector.getZ();
	result.SetX(x);
	result.SetY(y);
	result.SetZ(z);
}

template<>
void Rotate<ToWorldSpace>(const Matrix<3, 3>& Matrix, const Vector3& vector, Vector3& result)
{
	float x = Matrix.GetElementAt(0) * vector.getX() + Matrix.GetElementAt(3) * vector.getY() + Matrix.GetElementAt(6) * vector.getZ();
	float y = Matrix.GetElementAt(1) * vector.getX() + Matrix.GetElementAt(4) * vector.getY() + Matrix.GetElementAt(7) * vector.getZ();
	float z = Matrix.GetElementAt(2) * vector.getX() + Matrix.GetElementAt(5) * vector.getY() + Matrix.GetElementAt(8) * vector.getZ();
	result.SetX(x);
	result.SetY(y);
	result.SetZ(z);
}
}