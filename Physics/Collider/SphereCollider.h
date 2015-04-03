#pragma once
#include "Collider.h"

class RigidBody;

class SphereCollider : public Collider
{
public:
	SphereCollider(const Vector3& pos, const Vector3& displ, float radius);
	float GetRadius() const;
	static const int getType();
private:
	float _Radius;
	static const int _SphereColliderType;
};
