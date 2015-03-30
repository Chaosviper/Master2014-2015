#pragma once
#include "Vector3.h"

class RigidBody
{
public:
	RigidBody(const Vector3& Position, int ID, float Mass);
	RigidBody(const RigidBody& other);
	~RigidBody();
	void DoPhysic();
	void ApplyForce(const Vector3& force);
	int GetID() const;
	Vector3 GetPosition() const;
private:
	float _Mass;
	Vector3 _Position;
	int _ID;
};

