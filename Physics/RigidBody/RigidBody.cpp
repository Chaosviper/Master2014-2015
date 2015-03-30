#include "RigidBody.h"
#include "Physics.h"

RigidBody::RigidBody(const Vector3& Position, int ID, float Mass) : _Position(Position), _ID(ID), _Mass(Mass)
{
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
	Vector3 Force(Physics::Gravity*_Mass);

	// A = F / M
	DividiVettoreScalare(F, M, A);

	// A = A * DT -> nuova velocitˆ
	MoltiplicaVettoreScalare(A, DT, A);

	// V = V + A -> vecchia velocitˆ + nuova velocitˆ
	SommaVettori(V, A, V);

	/*** Considerando l'attrito dell'aria ***/
	InvertiVettore(V, tmpV);
	// Forza 0.5 = rho
	MoltiplicaVettoreScalare(tmpV, ModuloVettore(V) * 3.14 * 0.5 * 0.5, tmpV);
	// Accellerazione
	DividiVettoreScalare(tmpV, M, tmpV);
	// Velocitˆ
	MoltiplicaVettoreScalare(tmpV, DT, tmpV);
	SommaVettori(V, tmpV, V);

	// A = V * DT -> nuova posizione
	MoltiplicaVettoreScalare(V, DT, A);

	// P = P + A -> vecchia posizione + nuova posizione
	SommaVettori(P, A, P);

}

void RigidBody::ApplyForce(const Vector3& force)
{
}

Vector3 RigidBody::GetPosition() const
{
	return _Position;
}

int RigidBody::GetID() const
{
	return _ID;
}