#pragma once
#include "Collider.h"

class SphereCollider : public Collider
{
public:
	SphereCollider(RigidBody& body,const Vector3& displ, float radius);
	float GetRadius() const;
	static const int getType()
	{
		return SphereCollider::_SphereColliderType;
	};
private:
	float _Radius;
	static const int _SphereColliderType;
};
