#include "Physics.h"
#include "CollisionAlgorithms.h"

const float Physics::DeltaTime = 0.025f;
const Vector3 Physics::Gravity = Vector3(0, 9.8f, 0);

Physics::Physics()
{
	//OLD
	/*
	_Dispatcher.Add<BoxCollider, BoxCollider>(CollisionDetector::CubeCubeCollision);
	_Dispatcher.Add<BoxCollider, SphereCollider>(CollisionDetector::CubeSphereCollision);
	_Dispatcher.Add<SphereCollider, SphereCollider>(CollisionDetector::SphereSphereCollision);
	*/
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