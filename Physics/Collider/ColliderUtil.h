#pragma once
#include "TypeList.h"
#include "BoxCollider.h"
#include "SphereCollider.h"

namespace ColliderType
{
	typedef TYPELIST_2(BoxCollider, SphereCollider) ColliderTypeList;
}
