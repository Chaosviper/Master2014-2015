#pragma once
#include "Vector3.h"

class RigidBody
{
public:
	RigidBody(const Vector3& Position, int ID, float Mass);
	RigidBody(const RigidBody& other);
	~RigidBody();
	void DoPhysic();
	void ApplyForce(const Vector3& force, const Vector3& pointOfApplication);
	int GetID() const;
	float GetMass() const;
	Vector3 GetPosition() const;
	Vector3 GetVelocity() const;
	void SumForceToTotalForce(const Vector3&);
	void SumMomentumToTotalMomentum(const Vector3&);
	void SetPosition(const Vector3&);
	void SetVelocity(const Vector3&);
private:
	float _Mass;
	Vector3 _Position;
	Vector3 _Velocity;
	Vector3 _Inertia;
	Vector3 _AngularVelocity;
	Vector3 _QuantityOfMotion;
	Vector3 _AngularMomentum;
	Vector3 _ForceSum;
	Vector3 _MomentumSum;
		//TO DO
	//Quaternion _Rotation;
	//Matrix<3,3> _RotationMatrix;
	int _ID;
};

