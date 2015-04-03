#pragma once
#include "Collider.h"
class Quaternion;
class RigidBody;
class BoxCollider: public Collider
{
public:
	BoxCollider(const Vector3& pos, const Vector3& displ, const Quaternion& Rot);
	BoxCollider(const Vector3& pos, const Vector3& displ, const Quaternion& Rot, const Vector3& dimensions);

	static const int getType();
	const Quaternion& GetRotation() const;
	const Vector3& GetAxis(int i) const;
	const Vector3& GetFirstAxis();
	const Vector3& GetSecondAxis();
	const Vector3& GetThirdAxis();
	const Vector3& GetHalfSize() const;
	float GetSecondSize() const;
	float GetThirdSize() const;

private:
	static const int _BoxColliderType;
	const Quaternion* _Rotation;
	Vector3 _Center;
	Vector3 _HalfSize;
	Vector3 _Axises[3];
};