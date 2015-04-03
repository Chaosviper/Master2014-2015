#include "Physics.h"
#include "CollisionAlgorithms.h"
#include "RigidBody.h"
const float Physics::DeltaTime = 0.025f;
const Vector3 Physics::Gravity = Vector3(0, -1.8f, 0);

Physics::Physics()
{
	_Dispatcher.Add<BoxCollider, BoxCollider>(CollisionAlgorithm::CollisionDetectionAlgorithm<BoxCollider, BoxCollider>::Fire);
	_Dispatcher.Add<BoxCollider, SphereCollider>(CollisionAlgorithm::CollisionDetectionAlgorithm<BoxCollider, SphereCollider>::Fire<BoxCollider, SphereCollider>);
	_Dispatcher.Add<SphereCollider, BoxCollider>(CollisionAlgorithm::CollisionDetectionAlgorithm<BoxCollider, SphereCollider>::Fire<SphereCollider, BoxCollider>);
	_Dispatcher.Add<SphereCollider, SphereCollider>(CollisionAlgorithm::CollisionDetectionAlgorithm<SphereCollider, SphereCollider>::Fire);
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
		_RigidBodyList[index]->DoPhysic(Physics::DeltaTime);
		_RigidBodyList[index]->PrintStatus();
	}
	bool MaxCollisionReached = false;
	for (unsigned int index = 0; index < _RigidBodyList.size() && !MaxCollisionReached; ++index)
	{
		for (unsigned int index2 = index + 1; index2 < _RigidBodyList.size() && !MaxCollisionReached; ++index2)
		{
			MaxCollisionReached = _CollisionHandler.AddCollision(_Dispatcher.Dispatch(*(_RigidBodyList[index]->GetCollider()), *(_RigidBodyList[index2]->GetCollider())), _RigidBodyList[index], _RigidBodyList[index2]);
		}
	}
	_CollisionHandler.HandleCollision();
}

void Physics::AddRigidBody(RigidBody& Body, int ID)
{
	_RigidBodyIDs.push_back(ID);
	_RigidBodyList.push_back(&Body);
}

void Physics::ApplyForce(int ID, const Vector3& force, const Vector3& pointOfApplication)
{
	bool found = false;
	unsigned int index = 0;
	for (; index < _RigidBodyIDs.size()&&!found; ++index)
	{
		found = _RigidBodyIDs[index] == ID;
	}
	if (found)
	{
		_RigidBodyList[index]->ApplyForce(force, pointOfApplication);
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