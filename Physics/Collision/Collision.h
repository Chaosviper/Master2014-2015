#pragma once
#include "Vector3.h"

class RigidBody;

class Collision
{
public:
	Collision( RigidBody& first, RigidBody& second,const Vector3& force);
	void ApplyCollision();
private:
	RigidBody& _firstObj;
	RigidBody& _secondObj;
	Vector3 _force;
};