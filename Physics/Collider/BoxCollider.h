#pragma once
#include "Collider.h"

class BoxCollider: public Collider
{
public:
	BoxCollider(RigidBody& body, const Vector3& displ);
	BoxCollider(RigidBody& body, const Vector3& displ, const Vector3& center, const Vector3& firstAxis, const Vector3& secondAxis, const Vector3& thirdAxis, const Vector3& dimension);

	static const int getType();

	const Vector3& GetCenter() const;
	const Vector3& GetFirstAxis() const;
	const Vector3& GetSecondAxis() const;
	const Vector3& GetThirdAxis() const;

private:
	static const int _BoxColliderType;
	Vector3 _Center;
	Vector3 _HalfSize;
	Vector3 _Axises[3];
};