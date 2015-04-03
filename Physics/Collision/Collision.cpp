#include "Collision.h"
#include "RigidBody.h"
#include <iostream>
#include "Physics.h"
Collision::Collision(float deformation, const Vector3& pointOfApplication, const Vector3& normal)
: _deformation(deformation), _pointOfApplication(pointOfApplication), _normal(normal)
{
}

void Collision::ApplyCollision()
{
	//TO DO
	float f;
	float vn;
	float modVtang;
	vn = VectorOp::DotProduct(_force, _normal);
	Vector3 Vnorm = _normal*vn;
	Vector3 Vtang = _force - Vnorm;
	// K = coefficente elastico L = coefficente anaelastico  TO DO
	f = (0.5f * _deformation) + (5.0f * vn); 
	_normal *= f;
	// forza reagente (modulo) -> m = coefficente attrito TO DO
	f *= 5;	
	modVtang = Vtang.Modulus();
	if (f<0)
		f = 0;
	Vtang*=f;
	if (modVtang > 9.8f * Physics::DeltaTime) 
		Vtang.Normalize();
	else
		Vtang /= (9.8f * Physics::DeltaTime);
	
	_normal += Vtang;

	_firstObj->ApplyForce(_normal, _pointOfApplication);
	_secondObj->ApplyForce(_normal*-1.0f, _pointOfApplication);

	std::cout << "After Collision Handling" << std::endl;
	std::cout << "Collision Force: " << "( " << _normal.getX() << ", " << _normal.getY() << ", " << _normal.getZ() << ") " << std::endl;
	_firstObj->PrintStatus();
	_secondObj->PrintStatus();

};

void Collision::SetBodies(RigidBody*first,RigidBody*second)
{
	_firstObj = first;
	_secondObj = second;
	_force += first->GetVelocity();
	_force += second->GetVelocity();
}
