#include "BoxCollider.h"
#include "ColliderUtil.h"

const int BoxCollider::_BoxColliderType = ColliderType::TypeIndex::BOX;

const int  BoxCollider::getType()
{
	return BoxCollider::_BoxColliderType;
}

BoxCollider::BoxCollider(RigidBody& body, const Vector3& displ) 
	:Collider(_BoxColliderType, body, displ)
	{
	};

BoxCollider::BoxCollider(RigidBody& body, const Vector3& displ, 
	const Vector3& center, const Vector3& firstAxis, const Vector3& secondAxis, const Vector3& thirdAxis, const Vector3& dimension)
		:Collider(_BoxColliderType, body, displ),
			_Center(center), _HalfSize(dimension)
			{
				_Axises[0] = firstAxis;
				_Axises[0] = secondAxis;
				_Axises[0] = thirdAxis; 
			};


const Vector3& BoxCollider::GetCenter() const
{
	return _Center;
};

const Vector3& BoxCollider::GetFirstAxis() const
{
	return _Axises[0];
};

const Vector3& BoxCollider::GetSecondAxis() const
{
	return _Axises[1];
};

const Vector3& BoxCollider::GetThirdAxis() const
{
	return _Axises[3];
};