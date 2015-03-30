#include "Physics.h"
typedef RigidBodyList::iterator RigidBodyIterator;

const float Physics::DeltaTime = 0.025;
const Vector3 Physics::Gravity = Vector3(0, 9.8, 0);
Physics::Physics()
{
	_Dispatcher.Add<BoxCollider, BoxCollider>(CollisionDetector::CubeCubeCollision);
	_Dispatcher.Add<BoxCollider, SphereCollider>(CollisionDetector::CubeSphereCollision);
	_Dispatcher.Add<SphereCollider, SphereCollider>(CollisionDetector::SphereSphereCollision);
}

Physics::~Physics()
{
	for (unsigned int index = 0; index < _ColliderList.size(); ++index)
	{
		delete _ColliderList[index];
	}
	_ColliderList.clear();

	for (unsigned int index = 0; index < _RigidBodyList.size(); ++index)
	{
		delete _RigidBodyList[index];
	}
	_RigidBodyList.clear();
	_RigidBodyIDs.clear();
}

void Physics::ComputePhysic()
{
	for (unsigned int index = 0; index < _RigidBodyList.size(); ++index)
	{
		_RigidBodyList[index]->DoPhysic();
	}
	bool MaxCollisionReached = false;
	for (unsigned int index = 0; index < _ColliderList.size() && !MaxCollisionReached; ++index)
	{
		for (unsigned int index2 = index + 1; index2 < _ColliderList.size() && !MaxCollisionReached; ++index2)
		{
			MaxCollisionReached=_CollisionHandler.AddCollision(_Dispatcher.Dispatch( *(_ColliderList[index]), *(_ColliderList[index2]) ));
		}
	}
	
}

void Physics::AddRigidBody(RigidBody& Body, int ID)
{
	_RigidBodyIDs.push_back(ID);
	_RigidBodyList.push_back(&Body);
}

void Physics::ApplyForce(int ID, const Vector3& force)
{
	bool found = false;
	unsigned int index = 0;
	for (; index < _RigidBodyIDs.size()&&!found; ++index)
	{
		found = _RigidBodyIDs[index] == ID;
	}
	if (found)
	{
		_RigidBodyList[index]->ApplyForce(force);
	}
}

//MAYBE NON SENSE
void Physics::DeleteRigidBody(int ID)
{
	bool found = false;
	unsigned int index = 0;
	for (; index < _RigidBodyIDs.size() && !found; ++index)
	{
		found = _RigidBodyIDs[index] == ID;
	}
	if (found)
	{
		//TO DO
	}
}

void Physics::AddCollider(Collider* col)
{
	_ColliderList.push_back(col);
}