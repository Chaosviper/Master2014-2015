#pragma once
#include "Vector3.h"

class Collider abstract
{
public:
	int GetType() const;
	const Vector3 GetWorldPosition() const;
protected:
	void SetPosition(const Vector3& Pos);
	Collider(int type, const Vector3& displ);
private:
	int _Type;
	Vector3 _Displacement;
	const Vector3* _Position;
};

