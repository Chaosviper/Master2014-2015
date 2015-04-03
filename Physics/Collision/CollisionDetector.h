#pragma once/*
class Collider;
//OLD CLASS NO ONE USE IT
#include <iostream> //DEBUG ONLY
#include "Vector3.h"
#include "BoxCollider.h"
#include "SphereCollider.h"
#include "Collision.h"

class CollisionDetector
{
public:
	static Collision* CubeCubeCollision(Collider& first, Collider& second);
	static Collision* CubeSphereCollision(Collider& first, Collider& second);
	static Collision* SphereSphereCollision(Collider& first, Collider& second);

private:
	//template<typename T, typename U>
	//static void DetectCollision(T, U);
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
		float distance = Vector3::DistanceBetween(first->GetWorldPosition(), second->GetWorldPosition());
		float radiusSum = first->GetRadius() + second->GetRadius();
		float compenetrarion = distance-radiusSum;
		if (compenetrarion < 0)
		{
			//COMPUTE FORCE TO DO
			//return new Collision(first->GetRigidBody(),second->GetRigidBody(),Vector3(0,0,0));

		}
		return nullptr;
	};
};
*/