#pragma once
#include "BoxCollider.h"
#include "SphereCollider.h"
#include "Collision.h"

//For debug only
#include <iostream>

namespace CollisionAlgorithm
{
	template<class T, class U> class CollisionDetectionAlgorithm;

	template<>
	class CollisionDetectionAlgorithm<BoxCollider, BoxCollider>
	{
	public:
		
		static Collision* Fire(Collider& first, Collider& second)
		{
			return CollisionComputation(static_cast<BoxCollider*>(&first), static_cast<BoxCollider*>(&second));
		}
	private:
		
		static Collision* CollisionComputation(BoxCollider* first, BoxCollider* second)
		{
			//Fast reject




			std::cout << "Box Box" << std::endl;
			return nullptr;
		};
	};

	template<>
	class CollisionDetectionAlgorithm<SphereCollider, SphereCollider>
	{
	public:
		
		static Collision* Fire(Collider& first, Collider& second)
		{
			return CollisionComputation(static_cast<SphereCollider*>(&first), static_cast<SphereCollider*>(&second));
		}

	private:
		
		static Collision* CollisionComputation(SphereCollider* first, SphereCollider* second)
		{
			float distance = Vector3::DistanceBetween(first->GetWorldPosition(), second->GetWorldPosition());
			float radiusSum = first->GetRadius() + second->GetRadius();
			float compenetrarion = distance - radiusSum;
			if (compenetrarion < 0)
				//COMPUTE FORCE TO DO
				return new Collision(first->GetRigidBody(), second->GetRigidBody(), Vector3(0, 0, 0));
			else
				return nullptr;
			return nullptr;
		};
	};

	template<>
	class CollisionDetectionAlgorithm<BoxCollider, SphereCollider>
	{
	public:
		template<typename T, typename U>
		static Collision* Fire(Collider& first, Collider& second)
		{
			return CollisionComputation(static_cast<T*>(&first), static_cast<U*>(&second));
		};
		//for symmetry sake
		template<>
		static Collision* Fire<SphereCollider, BoxCollider>(Collider& first, Collider& second)
		{
			return CollisionComputation(static_cast<BoxCollider*>(&second), static_cast<SphereCollider*>(&first));
		}
	private:
		static Collision* CollisionComputation(BoxCollider* first, SphereCollider* second)
		{
			//DO SHIT
			std::cout << "Box Sphere" << std::endl;
			return nullptr;
		};
	};
}