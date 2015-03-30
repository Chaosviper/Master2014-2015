#include "BoxCollider.h"

const int BoxCollider::_BoxColliderType = ColliderMapping::BOX;

BoxCollider::BoxCollider(RigidBody& body, const Vector3& displ) 
	:Collider(_BoxColliderType, body, displ)
		{
		};