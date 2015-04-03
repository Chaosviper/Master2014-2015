#pragma once
#include <math.h>
#include "Vector3.h"
#include <iostream>
template<int Row,int Col>
class Matrix
{
	template<int,int>
	friend class Matrix;
public:
	float GetElementAt(int i, int j) const
	{
		return _matrix[i*Col + j];
	};
	float GetElementAt(int i) const
	{
		return _matrix[i];
	};
	void SetElementAt(int i,float val)
	{
		_matrix[i] = val;
	};
	
	void SetElementAt(int i, int j, float val)
	{
		_matrix[i*Col + j] = val;
	};
	void SetRow(int Nrow, float* value)
	{
		for (int i = 0; i < Col; ++i)
		{
			_matrix[Nrow*Col + i] = value[i];
		}
	};
	Matrix(){
		for (int i = 0; i < Row*Col; ++i)
		{
			_matrix[i] = 0;
		}
	}
	template<int OtherDim>
	float MultiplyRowCol(int Nrow, int Ncol, const Matrix<Col, OtherDim>& secondMatrix) const
	{
		float result = 0;
		const float* row = GetRow(Nrow);
		const float* col = secondMatrix.GetCol(Ncol);
		for (int i = 0; i < Col; ++i)
		{
			result += row[i] * col[i*Col];
		}
		return result;
	};

	Matrix(const Matrix<Row, Col>& other)
	{
		for (int i = 0; i < Row*Col; ++i)
		{
			
			_matrix[i] = other.GetElementAt(i);
		}
	}
	Matrix<Row, Col>& operator=(const Matrix<Row, Col> other)
	{
		if (this != &other)
		{
			for (int i = 0; i < Row*Col; i++)
				_matrix[i] = other.GetElementAt(i);
		}
		return *this;
	}
	Matrix<Col, Row>& Transpose()
	{
		Matrix<Col, Row> result;
		for (int i = 0; i < Row; ++i)
		{
			for (int j = 0; j < Col; ++j)
			{
				result.SetElementAt(j,i,GetElementAt(i, j));
			}
		}
		return result
	}
private:
	const float* GetRow(int i) const
	{
		return  &_matrix[i*Col];
	};
	const float* GetCol(int i)  const
	{
		return &_matrix[i];
	};

	float _matrix[Row*Col];
};

namespace MatrixOp{
	template<int Row, int Col, int secondMatrixCol>
	void MultiplyMatrix(const Matrix<Row, Col>& first, const Matrix<Col, secondMatrixCol>& second, Matrix<Row, secondMatrixCol>& result)
	{
		float rowR[secondMatrixCol];
		for (int i = 0; i < Row; ++i)
		{
			for (int j = 0; j < secondMatrixCol; ++j)
			{
				rowR[j] = first.MultiplyRowCol(i, j, second);
			}
			result.SetRow(i, rowR);
		}
	}
template<int Row, int Col>
void Rotate(const Matrix<Row, Col>& Matrix, const float* vector, float * result);

enum RotateTo
{
	ToWorldSpace = false,
	ToObjSpace = true
};
template<RotateTo To>
void Rotate(const Matrix<3, 3>& Matrix, const Vector3& vector, Vector3& result);
template<>
void Rotate<ToWorldSpace>(const Matrix<3, 3>& Matrix, const Vector3& vector, Vector3& result);
template<>
void Rotate<ToObjSpace>(const Matrix<3, 3>& Matrix, const Vector3& vector, Vector3& result);
}
