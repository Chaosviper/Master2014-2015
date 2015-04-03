#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "Physics.h"
#include "Quaternion.h"
#include "RigidBody.h"

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

Vector3 CuboidInertia(float mass, float width, float height,float depth)
{
	float x = mass*(height*height + depth*depth)/12;
	float y = mass*(width*width + depth*depth)/12;
	float z = mass*(height*height + width*width)/12;
	return Vector3(x, y, z);
}
Vector3 SphereInertia(float mass,float radius)
{
	float tmp = 2 * mass*radius*radius / 5;
	return Vector3(tmp,tmp,tmp);
}
int main()
{
	Physics p;
	Vector3 ones(1.0, 1.0, 1.0);
	Vector3 zeros(0.0, 0.0, 0.0);
	RigidBody* rB = new RigidBody(Vector3(1.0, 4.0, 1.0), 0, 5.0,SphereInertia(5,5));
	SphereCollider* sC = new SphereCollider(rB->GetPosition(),zeros, 5.0);
	rB->AttachCollider(sC);
	RigidBody* rB1 = new RigidBody(Vector3(8.0, 5.0, 4.0), 1, 4.0, SphereInertia(4, 1));
	SphereCollider* sC1 = new SphereCollider(rB1->GetPosition(), zeros, 1.0);
	rB1->AttachCollider(sC1);
	RigidBody* rB2 = new RigidBody(Vector3(8.0, 8.0, 4.0), 2, 4.0, SphereInertia(4, 3));
	SphereCollider* sC2 = new SphereCollider(rB2->GetPosition(), zeros, 3.0);
	rB2->AttachCollider(sC2);
	RigidBody* rB3 = new RigidBody(Vector3(10.0, 15.0, 19.0), 3, 9.0, SphereInertia(9, 2));
	SphereCollider* sC3 = new SphereCollider(rB3->GetPosition(), zeros, 2.0);
	rB3->AttachCollider(sC3);
	
	RigidBody* rB4 = new RigidBody(zeros,4,100,CuboidInertia(100,1,1,1));
	BoxCollider* bC = new BoxCollider(rB4->GetPosition(), zeros, rB4->GetRotationQuaternion());
	rB4->AttachCollider(bC);
	RigidBody* rB5 = new RigidBody(Vector3(1.0, 5.0, 4.0), 5, 10,CuboidInertia(10,1,1,1));
	BoxCollider* bC1 = new BoxCollider(rB5->GetPosition(), zeros, rB5->GetRotationQuaternion());
	rB5->AttachCollider(bC1);
	
	//p.AddRigidBody(*rB, rB->GetID());
	//p.AddRigidBody(*rB1, rB1->GetID());
	//p.AddRigidBody(*rB2, rB2->GetID());
	//p.AddRigidBody(*rB3, rB3->GetID());
	//p.AddRigidBody(*rB4, rB4->GetID());
	p.AddRigidBody(*rB5, rB5->GetID());
	//p.AddCollider(bC);
	//p.AddCollider(sC);
	//p.AddCollider(bC1);
	rB->ApplyForce(Vector3(1, 0, 0), Vector3(1.0, 3.0, 4.0));
	rB1->ApplyForce(zeros, ones);
	rB2->ApplyForce(Vector3(5,2,0),Vector3(8,0,0));
	rB5->ApplyForce(Vector3(50, 30, 75), Vector3(2, 6, 5));
	for (int i = 0; i < 5; ++i)
	{
		std::cout << "Iteration: " << i << std::endl;
		p.ComputePhysic();
		//system("PAUSE");
	}
	//Weird Test 
	/*
	Vector3 e(bC1->GetWorldPosition());
	Vector3 e1(bC->GetWorldPosition());
	Vector3 Min(e - bC1->GetHalfSize());
	Vector3 Max(e + bC1->GetHalfSize());

	Vector3 Min1(e1 - bC->GetHalfSize());
	Vector3 Max1(e1 + bC->GetHalfSize());

	printLine();
	std::cout << "center: "<<"(" << e[0] << ", " << e[1] << ", " << e[2] << ")" << std::endl;
	std::cout <<"Min: " <<"(" << Min[0] << ", " << Min[1] << ", " << Min[2] << ")" << std::endl;
	std::cout <<"Min: " <<"(" << Max[0] << ", " << Max[1] << ", " << Max[2] << ")" << std::endl;
	std::cout << "MinToHalf: " << "(" << (e - Min)[0] << ", " << (e - Min)[1] << ", " << (e - Min)[2] << ")" << std::endl;
	std::cout << "MaxToHalf: " << "(" << (Max - e)[0] << ", " << (Max - e)[1] << ", " << (Max - e)[2] << ")" << std::endl;
	std::cout << "center1: " << "(" << e1[0] << ", " << e1[1] << ", " << e1[2] << ")" << std::endl;
	std::cout << "Min1: " << "(" << Min1[0] << ", " << Min1[1] << ", " << Min1[2] << ")" << std::endl;
	std::cout << "Min1: " << "(" << Max1[0] << ", " << Max1[1] << ", " << Max1[2] << ")" << std::endl;
	std::cout << "Min1ToHalf: " << "(" << (e1-Min1)[0] << ", " << (e1-Min1)[1] << ", " << (e1-Min1)[2] << ")" << std::endl;
	std::cout << "Max1ToHalf: " << "(" << (Max1 - e1)[0] << ", " << (Max1 - e1)[1] << ", " << (Max1 - e1)[2] << ")" << std::endl;

	printLine();

	MatrixOp::Rotate<MatrixOp::ToObjSpace>(bC1->GetRotation().ToMatrix(), e, e);
	MatrixOp::Rotate<MatrixOp::ToObjSpace>(bC1->GetRotation().ToMatrix(), e1, e1);
	MatrixOp::Rotate<MatrixOp::ToObjSpace>(bC1->GetRotation().ToMatrix(), Min, Min);
	MatrixOp::Rotate<MatrixOp::ToObjSpace>(bC1->GetRotation().ToMatrix(), Max, Max);
	MatrixOp::Rotate<MatrixOp::ToObjSpace>(bC1->GetRotation().ToMatrix(), Min1, Min1);
	MatrixOp::Rotate<MatrixOp::ToObjSpace>(bC1->GetRotation().ToMatrix(), Max1, Max1);


	std::cout <<"centerRotated: "<< "(" << e[0] << ", " << e[1] << ", " << e[2] << ")" << std::endl;
	std::cout <<"Min: "<< "(" << Min[0] << ", " << Min[1] << ", " << Min[2] << ")" << std::endl;
	std::cout <<"Max: " <<"(" << Max[0] << ", " << Max[1] << ", " << Max[2] << ")" << std::endl;
	std::cout << "MinToHalfRotated: " << "(" << (e - Min)[0] << ", " << (e - Min)[1] << ", " << (e - Min)[2] << ")" << std::endl;
	std::cout << "MaxToHalfRotated: " << "(" << (Max - e)[0] << ", " << (Max - e)[1] << ", " << (Max - e)[2] << ")" << std::endl;


	std::cout <<"center1Rotated: " <<"(" << e1[0] << ", " << e1[1] << ", " << e1[2] << ")" << std::endl;
	std::cout << "Min1: " << "(" << Min1[0] << ", " << Min1[1] << ", " << Min1[2] << ")" << std::endl;
	std::cout << "Min1: " << "(" << Max1[0] << ", " << Max1[1] << ", " << Max1[2] << ")" << std::endl;
	std::cout << "Min1ToHalfRotated: " << "(" << (e1 - Min1)[0] << ", " << (e1 - Min1)[1] << ", " << (e1 - Min1)[2] << ")" << std::endl;
	std::cout << "Max1ToHalfRotated: " << "(" << (Max1 - e1)[0] << ", " << (Max1 - e1)[1] << ", " << (Max1 - e1)[2] << ")" << std::endl;

	printLine();

	Min = (e - bC1->GetHalfSize());
	Max = (e + bC1->GetHalfSize());
	Min1 = (e1 - bC->GetHalfSize());
	Max1 = (e1 + bC->GetHalfSize());

	std::cout << "Min: "<<"(" << Min[0] << ", " << Min[1] << ", " << Min[2] << ")" << std::endl;
	std::cout << "Max: "<<"(" << Max[0] << ", " << Max[1] << ", " << Max[2] << ")" << std::endl;
	std::cout << "MinToHalfFromRotatedcenter: " << "(" << (e - Min)[0] << ", " << (e - Min)[1] << ", " << (e - Min)[2] << ")" << std::endl;
	std::cout << "MaxToHalfFromRotatedcenter: " << "(" << (Max - e)[0] << ", " << (Max - e)[1] << ", " << (Max - e)[2] << ")" << std::endl;

	std::cout << "center1Rotated: " << "(" << e1[0] << ", " << e1[1] << ", " << e1[2] << ")" << std::endl;
	std::cout << "Min1: " << "(" << Min1[0] << ", " << Min1[1] << ", " << Min1[2] << ")" << std::endl;
	std::cout << "Min1: " << "(" << Max1[0] << ", " << Max1[1] << ", " << Max1[2] << ")" << std::endl;
	std::cout << "Min1ToHalfFromRotatedcenter: " << "(" << (e1 - Min1)[0] << ", " << (e1 - Min1)[1] << ", " << (e1 - Min1)[2] << ")" << std::endl;
	std::cout << "Max1ToHalfFromRotatedcenter: " << "(" << (Max1 - e1)[0] << ", " << (Max1 - e1)[1] << ", " << (Max1 - e1)[2] << ")" << std::endl;
	*/
	system("PAUSE");
};