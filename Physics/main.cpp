#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "Physics.h"
#include "Matrix.h"

template<int Row,int Col>
void printMatrix(Matrix<Row,Col> matrix)
{
	for (int i = 0; i < Row; ++i)
	{
		for (int j = 0; j < Col; ++j){
			std::cout << matrix.GetElementAt(i, j);
		}
		std::cout << std::endl;
	}
}
void printLine()
{
	std::cout << "---------------------------- \n" << std::endl;
}

int main()
{
	Physics p;
	Vector3 ones(1, 1, 1);
	Vector3 zeros(0, 0, 0);
	RigidBody* rB = new RigidBody(ones,0,10);
	SphereCollider* sC = new SphereCollider(*rB, zeros, 5);
	RigidBody* rB1 = new RigidBody(zeros,1,10);
	BoxCollider* bC = new BoxCollider(*rB1, zeros);
	p.AddRigidBody(*rB, rB->GetID());
	p.AddRigidBody(*rB1, rB1->GetID());
	p.AddCollider(sC);
	p.AddCollider(bC);
	p.ComputePhysic();

	printLine();
	std::cout << "Matrix test \n" << std::endl;
	//Matrix test
	Matrix<3, 3> m1;
	Matrix<3, 3> m2;
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			m1.SetElementAt(i, j, i);
			m2.SetElementAt(i, j, j);
		}
	}
	printMatrix(m1);
	printLine();
	printMatrix(m2);
	printLine();
	MatrixOp::MultiplyMatrix(m1, m2, m1);
	printMatrix(m1);
	printLine();

	system("PAUSE");
};