#pragma once
#include "Collision.h"
#include "Collider.h"
#include "BoxCollider.h"
#include "SphereCollider.h"
#include <iostream> //DEBUG ONLY

class CollisionDetector
{
public:
	static Collision* CubeCubeCollision(Collider& first,Collider& second)
	{
		return DetectCollision(static_cast<BoxCollider*>(&first), static_cast<BoxCollider*>(&second));
	}

	static Collision* CubeSphereCollision(Collider& first, Collider& second)
	{
		return DetectCollision(static_cast<BoxCollider*>(&first), static_cast<SphereCollider*>(&second));
	}

	static Collision* SphereSphereCollision(Collider& first, Collider& second)
	{
		return DetectCollision(static_cast<SphereCollider*>(&first), static_cast<SphereCollider*>(&second));
	}

private:
	template<typename T, typename U>
	static void DetectCollision(T, U);
	static Collision* DetectCollision(BoxCollider* first, BoxCollider* second)
	{
		//DO SHIT
		std::cout << "Box Box" << std::endl;
		return nullptr;
	};
	static Collision* DetectCollision(BoxCollider* first, SphereCollider* second)
	{
		//DO SHIT
		std::cout << "Box Sphere" << std::endl;
		return nullptr;
	};
	static Collision* DetectCollision(SphereCollider* first, SphereCollider* second)
	{
		float distance = Vector3::DistanceBetween(first->GetPosition(), second->GetPosition());
		float radiusSum = first->GetRadius() + second->GetRadius();
		float compenetrarion = distance-radiusSum;
		if (compenetrarion < 0)
			//COMPUTE FORCE TO DO
			return new Collision(first->GetRigidBody(),second->GetRigidBody(),Vector3(0,0,0));
		else
			return nullptr;
	};
};