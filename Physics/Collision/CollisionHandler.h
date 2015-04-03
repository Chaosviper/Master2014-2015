#pragma once
#include <vector>
#include "Collision.h"
#include <iostream>
template<
	int MaxCollision
>
class CollisionHandler
{
	typedef std::vector<Collision*> CollisionCollection;
	typedef CollisionCollection::iterator Iterator;
public:
	void HandleCollision() 
	{
		int i = 0;
		for (Iterator collision = _CollisionList.begin(); collision != _CollisionList.end(); ++collision,++i)
		{
			(*collision)->ApplyCollision();
		}
		std::cout << "Total Collision Handled: " << i << std::endl;
		Clear();
	}

	bool AddCollision(Collision* col,RigidBody* first,RigidBody* second)
	{
		if (_CollisionList.size() < MaxCollision && col != nullptr)
		{
			col->SetBodies(first,second);
			_CollisionList.push_back(col);
		}
		return _CollisionList.size() == MaxCollision;
	}
	void Clear()
	{
		for (Iterator collision = _CollisionList.begin(); collision != _CollisionList.end(); ++collision)
		{
			delete *collision;
		}
		_CollisionList.clear();
	}
	
	CollisionHandler()
	{
		_CollisionList.reserve(MaxCollision);
	}

private:
	CollisionCollection _CollisionList;
};
