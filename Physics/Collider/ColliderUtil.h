#pragma once
#include "TypeList.h"
#include "BoxCollider.h"
#include "SphereCollider.h"

namespace ColliderType
{

	typedef TYPELIST_2(BoxCollider, SphereCollider) ColliderTypeList;
	typedef TL::Length<ColliderTypeList> ColliderTypeListSize;

	enum TypeIndex
	{
		BOX = TL::IndexOf<ColliderTypeList, BoxCollider>::value,
		SPHERE = TL::IndexOf<ColliderTypeList, SphereCollider>::value,
		//		END = TL::IndexOf<ColliderTypeList, NullType>::value
	};

	//	static const TypeIndex Begin = TypeIndex::BOX;
	//static const TypeIndex End = TypeIndex::END;
}
