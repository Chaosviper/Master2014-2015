#include "SphereCollider.h"
const int SphereCollider::_SphereColliderType= ColliderMapping::SPHERE;

SphereCollider::SphereCollider(RigidBody& body,const Vector3& displ, float radius)
	:Collider(_SphereColliderType, body, displ), _Radius(radius)
		{
		};

float SphereCollider::GetRadius() const
{
	return _Radius;
}