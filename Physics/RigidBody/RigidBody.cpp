#include "RigidBody.h"
#include "Physics.h"

RigidBody::RigidBody(const Vector3& Position, int ID, float Mass) : _Position(Position), _ID(ID), _Mass(Mass)
{
	_Velocity=Vector3::zeroes();
	_Inertia = Vector3::zeroes();
	_AngularVelocity = Vector3::zeroes();
	_QuantityOfMotion = Vector3::zeroes();
	_AngularMomentum = Vector3::zeroes();
	_ForceSum = Vector3::zeroes();
	_MomentumSum = Vector3::zeroes();
}

RigidBody::RigidBody(const RigidBody& other)
{
	_Position = other.GetPosition();
}

RigidBody::~RigidBody()
{
}

void RigidBody::DoPhysic(float DeltaTime)
{
	Vector3 tmp(_ForceSum*DeltaTime);
	_QuantityOfMotion=_QuantityOfMotion+tmp;
	tmp = _MomentumSum*DeltaTime;
	_AngularMomentum += tmp;
	_Velocity=_QuantityOfMotion / _Mass;
	tmp = _Velocity*DeltaTime;
	_Position += tmp;
	float r[3];
	MatrixOp::RotateRelative(_RotationMatrix, _AngularMomentum.GetData(), r);
	_AngularVelocity.SetX(r[0] / _Inertia.getX());
	_AngularVelocity.SetY(r[1] / _Inertia.getY());
	_AngularVelocity.SetZ(r[2] / _Inertia.getZ());

	Quaternion Rot(1, _AngularVelocity.getX()*DeltaTime / 2, _AngularVelocity.getY()*DeltaTime / 2, _AngularVelocity.getZ()*DeltaTime / 2);

	Normalize(Rot);
	_Rotation = _Rotation*Rot;
	Normalize(_Rotation);

	MatrixOp::RotateAbsolute(_RotationMatrix, _AngularVelocity.GetData(), r);
	_AngularVelocity.SetX(r[0]);
	_AngularVelocity.SetY(r[1]);
	_AngularVelocity.SetZ(r[2]);
	_RotationMatrix=_Rotation.ToMatrix();
}

float RigidBody::GetMass() const
{
	return _Mass;
}

void RigidBody::ApplyForce(const Vector3& force,const Vector3& pointOfApplication)
{
	SumForceToTotalForce(force);
	Vector3 ForceOnPoint(pointOfApplication - GetPosition());
	VectorialProduct(ForceOnPoint,force,ForceOnPoint);
	SumMomentumToTotalMomentum(ForceOnPoint);
}

Vector3 RigidBody::GetVelocity() const
{
	return _Velocity;
};
Vector3 RigidBody::GetPosition() const
{
	return _Position;
}

int RigidBody::GetID() const
{
	return _ID;
}

void RigidBody::SetVelocity(const Vector3& NewVelocity)
{
	_Velocity = NewVelocity;
};

void RigidBody::SetPosition(const Vector3& NewPosition)
{
	_Position = NewPosition;
};

void RigidBody::SumForceToTotalForce(const Vector3& force)
{
	_ForceSum += force;
};

void RigidBody::SumMomentumToTotalMomentum(const Vector3& momentum)
{
	_MomentumSum += momentum;
};