#include "ColliderUtil.h"

ColliderType::TypeIndex& operator++(ColliderType::TypeIndex& target)
{
	target = static_cast< ColliderType::TypeIndex >(target + 1);
	return target;
};

