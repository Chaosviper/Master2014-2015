#pragma once
#include "RigidBody.h"
#include "Vector3.h"

class Collider abstract
{
public:
	int GetType() const;
	Vector3 GetWorldPosition() const;
	RigidBody& GetRigidBody() const;
protected:
	Collider(int type,RigidBody& body,const Vector3& displ);
private:
	int _Type;
	RigidBody& _RigidBody;
	Vector3 _Displacement;
};