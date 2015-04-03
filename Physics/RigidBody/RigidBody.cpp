#include "RigidBody.h"

#include "Collider.h"
#include "Physics.h"
#include <iostream>
void Print(const Vector3& v)
{
	std::cout << "(" << v.getX() << ", " << v.getY() << ", " << v.getZ() << ")" << std::endl;
}

void Print(const Quaternion& v)
{
	std::cout << "(" << v.GetValue(0) << ", " << v.GetValue(1) << ", " << v.GetValue(2) << ", " << v.GetValue(3) << ")" << std::endl;
}
void Print(const Matrix<3, 3>& m)
{
	std::cout << m.GetElementAt(0) << ", " << m.GetElementAt(1) << ", " << m.GetElementAt(2) << std::endl;
	std::cout << m.GetElementAt(3) << ", " << m.GetElementAt(4) << ", " << m.GetElementAt(5) << std::endl;
	std::cout << m.GetElementAt(6) << ", " << m.GetElementAt(7) << ", " << m.GetElementAt(8) << std::endl;
}
RigidBody::RigidBody(const Vector3& Position, int ID, float Mass,const Vector3& Inertia) : _Position(Position), _ID(ID), _Mass(Mass)
{
	_Velocity=VectorOp::Zero;
	_Inertia = Inertia;
	_AngularVelocity = VectorOp::Zero;
	_QuantityOfMotion = VectorOp::Zero;
	_AngularMomentum = VectorOp::Zero;
	_ForceSum = VectorOp::Zero;
	_MomentumSum = VectorOp::Zero;
	_RotationMatrix = _Rotation.ToMatrix();
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
	
	_QuantityOfMotion+=tmp;
	tmp = _MomentumSum*DeltaTime;
	_AngularMomentum += tmp;
	_Velocity=_QuantityOfMotion / _Mass;
	tmp = _Velocity*DeltaTime;
	_Position += tmp;
	
	MatrixOp::Rotate<MatrixOp::ToObjSpace>(_RotationMatrix, _AngularMomentum, _AngularVelocity);

	_AngularVelocity.SetX(_AngularVelocity.getX() / _Inertia.getX());
	_AngularVelocity.SetY(_AngularVelocity.getY() / _Inertia.getY());
	_AngularVelocity.SetZ(_AngularVelocity.getZ() / _Inertia.getZ());

	Quaternion Rot(1, _AngularVelocity.getX()*DeltaTime / 2, _AngularVelocity.getY()*DeltaTime / 2, _AngularVelocity.getZ()*DeltaTime / 2);

	Rot.Normalize();
	_Rotation = _Rotation*Rot;
	_Rotation.Normalize();
	MatrixOp::Rotate<MatrixOp::ToWorldSpace>(_RotationMatrix, _AngularVelocity, _AngularVelocity);
	
	_RotationMatrix=_Rotation.ToMatrix();
	_ForceSum += Physics::Gravity*_Mass;
}

float RigidBody::GetMass() const
{
	return _Mass;
}

void RigidBody::ApplyForce(const Vector3& force,const Vector3& pointOfApplication)
{
	SumForceToTotalForce(force);
	Vector3 ForceOnPoint(pointOfApplication-_Position);
	VectorOp::VectorialProduct(ForceOnPoint, force, ForceOnPoint);
	SumMomentumToTotalMomentum(ForceOnPoint);
}

Vector3 RigidBody::GetVelocity() const
{
	return _Velocity;
};
const Vector3& RigidBody::GetPosition() const
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

const Matrix<3, 3>& RigidBody::GetRotationMatrix() const
{
	return _RotationMatrix;
};

const Quaternion& RigidBody::GetRotationQuaternion() const
{
	return _Rotation;
};

void RigidBody::AttachCollider(Collider* Collider)
{
	_Collider = Collider;
}

void RigidBody::DetachCollider()
{
	delete _Collider;
}

void RigidBody::PrintStatus()
{
	std::cout << "----------------------------- \n" << std::endl;
	std::cout << "RigidBody: " << _ID << std::endl;
	std::cout << "Mass: " << _Mass << std::endl;
	std::cout << "Position: ";
	Print(_Position);
	std::cout << "Velocity: ";
	Print(_Velocity);
	std::cout << "Inertia: ";
	Print(_Inertia);
	std::cout << "AngularVelocity: ";
	Print(_AngularVelocity);
	std::cout << "QuantityOfMotion: ";
	Print(_QuantityOfMotion);
	std::cout << "AngularMomentum: ";
	Print(_AngularMomentum);
	std::cout << "ForceSum: ";
	Print(_ForceSum);
	std::cout << "MomentumSum: ";
	Print(_MomentumSum);
	std::cout << "Rotation: ";
	Print(_Rotation);
	std::cout << "RotationMatrix: \n";
	Print(_RotationMatrix);
	std::cout << "----------------------------- \n" << std::endl;
}

 Collider* RigidBody::GetCollider() const
{
	return _Collider;
};