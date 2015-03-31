#include "Collider.h"

Collider::Collider(int type,RigidBody& body,const Vector3& displ) : _Type(type), _RigidBody(body), _Displacement(displ)
{
};

RigidBody& Collider::GetRigidBody() const
{
	return _RigidBody;
}

Vector3 Collider::GetWorldPosition() const
{
	return _RigidBody.GetPosition() + _Displacement;
}

int Collider::GetType() const
{
	return _Type;
};