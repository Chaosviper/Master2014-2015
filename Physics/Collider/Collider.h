#pragma once
#include "RigidBody.h"
#include "Vector3.h"
namespace ColliderMapping{
	//USED FOR INDEXING ARRAY ON DISPATCHER FOR CALLING RIGHT CALLBACK 
	enum
	{
		BOX,
		SPHERE
	};
};
class Collider abstract
{
public:
	int GetType() const
	{
		return _Type;
	};
	Vector3 GetPosition() const;
	RigidBody& GetRigidBody() const;
protected:
	Collider(int type,RigidBody& body,const Vector3& displ);
private:
	int _Type;
	RigidBody& _RigidBody;
	Vector3 _Displacement;
};