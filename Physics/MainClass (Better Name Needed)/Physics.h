#pragma once
#include <vector>
#include "CollisionHandler.h"
#include "Dispatcher.h"
#include "ColliderUtil.h"

class RigidBody;

typedef ColliderType::ColliderTypeList CollidersType;
typedef CollisionHandler<20> PhysicCollisionHandler;
typedef std::vector<RigidBody*> RigidBodyList;
typedef std::vector<Collider*> ColliderList;
typedef Dispatcher<Collider, CollidersType, Collision*> ColliderDispatcher;
typedef std::vector<int> RigidBodyID;

class Physics
{
public:
	Physics();
	~Physics();
	void ComputePhysic();
	void AddRigidBody(RigidBody& RigidBody, int ID);
	void ApplyForce(int ID, const Vector3& force,const Vector3& pointOfApplication);
	void DeleteRigidBody(int ID);
	void AddCollider(Collider* Col);
	static const float DeltaTime;
	static const Vector3 Gravity;
private:
	Physics(const Physics& other);
	Physics& operator=(const Physics& other);
	PhysicCollisionHandler _CollisionHandler;
	RigidBodyID _RigidBodyIDs;
	RigidBodyList _RigidBodyList;
	ColliderList _ColliderList;
	ColliderDispatcher _Dispatcher;
};


