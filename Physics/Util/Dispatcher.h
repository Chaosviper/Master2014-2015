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
		//with upper triangular matrix 
		//_callbacks[leftIndex + rightIndex] = funcPtr;
		
		//with NxN matrix
		_callbacks[leftIndex*Size::value + rightIndex] = funcPtr;

		//std::vector NOT TESTED
		//if(leftIndex*Size::value + rightIndex>_callbacks.capacity());
		//{
		//	_callbacks.resize(leftIndex*Size::value + rightIndex + 1);
		//}
		//_callbacks[leftIndex*Size::value + rightIndex] = funcPtr;
	}

	ReturnType Dispatch(Type& firstArg, Type& secondArg)
	{
		//Symmetry check need for upper triangular matrix
		//if (firstArg.GetType() > secondArg.GetType())
		//{
			return _callbacks[firstArg.GetType() + secondArg.GetType()](firstArg, secondArg);
		//}
		//else
		//{
		//	return _callbacks[firstArg.GetType() + secondArg.GetType()](secondArg,firstArg);
		//}
		
	}

private:
	//upper triangular matrix need symmetry 
	//CallbackType _callbacks[(Size::value + 1)*Size::value / 2];
	
	//NxN Matrix 
	CallbackType _callbacks[Size::value*Size::value];

	//std::vector
	//typedef std::vector<CallbackType> CallbackCollection
	//CallbackCollection _callbacks;

};