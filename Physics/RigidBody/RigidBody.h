#pragma once
#include "Matrix.h"
#include "Vector3.h"
#include "Quaternion.h"
class Collider;
template<int row, int col>
class Matrix;
class RigidBody
{
public:
	RigidBody(const Vector3& Position, int ID, float Mass,const Vector3& Inertia);
	RigidBody(const RigidBody& other);
	~RigidBody();
	void DoPhysic(float);
	void ApplyForce(const Vector3& force, const Vector3& pointOfApplication);
	int GetID() const;
	float GetMass() const;
	const Matrix<3,3>& GetRotationMatrix() const;
	const Vector3& GetPosition() const;
	Vector3 GetVelocity() const;
	void SumForceToTotalForce(const Vector3&);
	void SumMomentumToTotalMomentum(const Vector3&);
	void SetPosition(const Vector3&);
	void SetVelocity(const Vector3&);
	const Quaternion& GetRotationQuaternion() const;
	void AttachCollider(Collider*);
	void DetachCollider();
	void PrintStatus();
	Collider* GetCollider() const;
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
	Quaternion _Rotation;
	Matrix<3,3> _RotationMatrix;
	Collider* _Collider;
	int _ID;
};

