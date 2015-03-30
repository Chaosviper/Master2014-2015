#pragma once
#include "TypeList.h"

template<
	class Type,
	class TypeList,
	typename ReturnType= void,
	typename CallbackType = ReturnType(*)(Type&, Type&)
	>
class Dispatcher
{
	typedef typename TL::Length< TypeList > Size;

public:
	template<class LeftArg,class RightArg>
	void Add(CallbackType funcPtr)
	{
		int leftIndex = LeftArg::getType();
		int rightIndex = RightArg::getType();
		_callbacks[leftIndex + rightIndex] = funcPtr;
	}

	ReturnType Dispatch(Type& firstArg, Type& secondArg)
	{
		if (firstArg.GetType() > secondArg.GetType())
		{
			return _callbacks[firstArg.GetType() + secondArg.GetType()](firstArg, secondArg);
		}
		else
		{
			return _callbacks[firstArg.GetType() + secondArg.GetType()](secondArg,firstArg);
		}
		
	}

private:
	CallbackType _callbacks[(Size::value + 1)*Size::value / 2];
};