#include "SphereCollider.h"
#include "ColliderUtil.h"

const int SphereCollider::_SphereColliderType = ColliderType::TypeIndex::SPHERE;

SphereCollider::SphereCollider(RigidBody& body,const Vector3& displ, float radius)
	:Collider(_SphereColliderType, body, displ), _Radius(radius)
		{
		};

float SphereCollider::GetRadius() const
{
	return _Radius;
}

const int SphereCollider::getType()
{
	return SphereCollider::_SphereColliderType;
};