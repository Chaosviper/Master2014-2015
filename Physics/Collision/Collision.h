#pragma once
#include "Vector3.h"

class RigidBody;

class Collision
{
public:
	Collision(float deformation, const Vector3& pointOfApplication, const Vector3& normal);
	void SetBodies(RigidBody* first,RigidBody* second);
	void ApplyCollision();
private:
	RigidBody* _firstObj;
	RigidBody* _secondObj;
	float _deformation;
	Vector3 _pointOfApplication;
	Vector3 _force;
	Vector3 _normal;
};