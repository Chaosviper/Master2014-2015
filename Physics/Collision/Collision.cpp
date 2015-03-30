#include "Collision.h"
#include "RigidBody.h"
Collision::Collision(RigidBody& first,RigidBody& second, const Vector3& force)
:_firstObj(first), _secondObj(second), _force(force)
{
}

void Collision::ApplyCollision()
{
	_firstObj.ApplyForce(_force);
	//CHANGE FORCE DIRECTION TO DO
	_secondObj.ApplyForce(_force);
};