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

void RigidBody::DoPhysic()
{
	//SILLY THING
	Vector3 Force(Physics::Gravity*GetMass());
	Vector3 Acceleration(Force / GetMass());
	Acceleration *= Physics::DeltaTime;
	SetVelocity(GetVelocity() + Acceleration);
	SetPosition(GetPosition() + Acceleration);

	/* TO DO*/
/*	float v[3];
	float q[4];

	MoltiplicaVettoreScalare(Fris, dt, v);
	SommaVettori(v, Qmoto, Qmoto);
	MoltiplicaVettoreScalare(Mris, dt, v);
	SommaVettori(v, Mang, Mang);

	DividiVettoreScalare(Qmoto, Massa, Vel);
	MoltiplicaVettoreScalare(Vel, dt, v);
	SommaVettori(v, Pos, Pos);

	RuotaRelative(MRot, Mang, Vang); // Per risolvere problemi di inerzia, raddrizzo il mio
	// oggetto, altrimenti l'inerzia cambierebbe in base a come è disposto l'oggetto

	Vang[0] /= Inerzia[0];
	Vang[1] /= Inerzia[1];
	Vang[2] /= Inerzia[2];

	q[0] = 1;
	q[1] = Vang[0] * dt / 2;
	q[2] = Vang[1] * dt / 2;
	q[3] = Vang[2] * dt / 2;

	NormalizzaQuaternione(q, q);
	MoltiplicaQuaternioni(Rot, q, Rot);
	NormalizzaQuaternione(Rot, Rot);

	RuotaAssolute(MRot, Vang, Vang); // Torno in assoluto per poi tornare in relativo
	MatriceDaQuaternione(Rot, MRot);

	*/
}

float RigidBody::GetMass() const
{
	return _Mass;
}

void RigidBody::ApplyForce(const Vector3& force,const Vector3& pointOfApplication)
{
	SumForceToTotalForce(force);
	Vector3 ForceOnPoint(pointOfApplication - GetPosition());
	SumMomentumToTotalMomentum(ForceOnPoint * force);
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