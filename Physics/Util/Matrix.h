#pragma once
#include <math.h>
//Debug Only
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
void MultiplyMatrix(const Matrix<Row, Col>& first,const Matrix<Col, secondMatrixCol>& second, Matrix<Row, secondMatrixCol>& result)
{
	float rowR[secondMatrixCol];
	for (int i = 0; i < Row; ++i)
	{
		for (int j = 0; j < secondMatrixCol; ++j)
		{
			rowR[j] = first.MultiplyRowCol(i, j, second);
			//result.SetElementAt(i, j, first.MultiplyRowCol(i, j, second));
		}
		result.SetRow(i, rowR);
	}
}
template<int Row,int Col>
void RotateAbsolute(Matrix<Row, Col>& Matrix, const float* vector, float * result)
{
	//Cattani
	//o3[0] = Matrice3x3[0] * X + Matrice3x3[3] * Y + Matrice3x3[6] * Z;
	//o3[1] = Matrice3x3[1] * X + Matrice3x3[4] * Y + Matrice3x3[7] * Z;
	//o3[2] = Matrice3x3[2] * X + Matrice3x3[5] * Y + Matrice3x3[8] * Z;
	for (int i = 0; i < Col; ++i)
	{
		result[i] = 0;
		for (int j = 0; j < Row; ++j)
		{
			result[i] += Matrix.GetElementAt(j, i) * vector[j];
		}
	}
}
template<int Row, int Col>
void RotateRelative(Matrix<Row, Col>& Matrix, const float* vector, float * result)
{
	//Cattani
	//	o3[0] = Matrice3x3[0] * X + Matrice3x3[1] * Y + Matrice3x3[2] * Z;
	//	o3[1] = Matrice3x3[3] * X + Matrice3x3[4] * Y + Matrice3x3[5] * Z;
	//	o3[2] = Matrice3x3[6] * X + Matrice3x3[7] * Y + Matrice3x3[8] * Z;

	for (int i = 0; i < Row; ++i)
	{
		result[i] = 0;
		for (int j = 0; j < Col; ++j)
		{
			result[i] += Matrix.GetElementAt(i, j) * vector[j];
		}
	}

}
}
