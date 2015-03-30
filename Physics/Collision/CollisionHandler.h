#pragma once
#include <vector>
#include "Collision.h"

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
		for (Iterator i = _CollisionList.begin(); i !=_CollisionList.end(); ++i)
		{
			_CollisionList[i]->ApplyCollision();
		}
		_CollisionList.clear();
	}

	bool AddCollision(Collision* col)
	{
		bool tmp = _CollisionList.size() < MaxCollision;
		if (tmp && col!=nullptr)
		{
			_CollisionList.push_back(col);
		}
		return tmp;
	}
	CollisionHandler()
	{
		_CollisionList.reserve(MaxCollision);
	}
private:
	CollisionCollection _CollisionList;
};
