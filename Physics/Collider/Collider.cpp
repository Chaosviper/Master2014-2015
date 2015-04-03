#include "Collider.h"
#include <iostream>
Collider::Collider(int type,const Vector3& displ) : _Type(type), _Displacement(displ)
{
};

const Vector3 Collider::GetWorldPosition() const
{
	return *(_Position)+_Displacement;
}

int Collider::GetType() const
{
	return _Type;
};
void Collider::SetPosition(const Vector3& Pos)
{
	_Position = &Pos;
}
