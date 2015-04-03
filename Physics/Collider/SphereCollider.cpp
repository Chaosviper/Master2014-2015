#include "SphereCollider.h"
#include "ColliderUtil.h"

const int SphereCollider::_SphereColliderType = ColliderType::TypeIndex::SPHERE;

SphereCollider::SphereCollider(const Vector3& pos, const Vector3& displ, float radius)
	:Collider(_SphereColliderType, displ), _Radius(radius)
		{
		SetPosition(pos);
		};

float SphereCollider::GetRadius() const
{
	return _Radius;
}

const int SphereCollider::getType()
{
	return SphereCollider::_SphereColliderType;
};