#pragma once
#include "Collider.h"

class BoxCollider: public Collider
{
public:
	BoxCollider(RigidBody& body, const Vector3& displ);
	static const int getType()
	{
		return BoxCollider::_BoxColliderType;
	}
private:
	static const int _BoxColliderType;
};

