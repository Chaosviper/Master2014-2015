#include "CollisionDetector.h"

Collision* CollisionDetector::CubeCubeCollision(Collider& first, Collider& second)
{
	return DetectCollision(static_cast<BoxCollider*>(&first), static_cast<BoxCollider*>(&second));
}

Collision* CollisionDetector::CubeSphereCollision(Collider& first, Collider& second)
{
	return DetectCollision(static_cast<BoxCollider*>(&first), static_cast<SphereCollider*>(&second));
}

Collision* CollisionDetector::SphereSphereCollision(Collider& first, Collider& second)
{
	return DetectCollision(static_cast<SphereCollider*>(&first), static_cast<SphereCollider*>(&second));
}