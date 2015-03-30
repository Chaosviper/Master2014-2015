#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "Physics.h"

int main()
{
	Physics p;
	Vector3 ones(1, 1, 1);
	Vector3 zeros(0, 0, 0);
	RigidBody* rB	=new RigidBody(ones,0,10);
	SphereCollider* sC	= new SphereCollider(*rB, zeros, 5);
	RigidBody* rB1= new RigidBody(zeros,1,10);
	BoxCollider* bC=new BoxCollider(*rB1, zeros);
	p.AddRigidBody(*rB, rB->GetID());
	p.AddRigidBody(*rB1, rB1->GetID());
	p.AddCollider(sC);
	p.AddCollider(bC);
	p.ComputePhysic();
	system("PAUSE");
};