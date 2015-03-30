#pragma once
class NullType{};

template< typename T, typename U> 
struct Typelist 
{
	typedef T Head;
	typedef U Tail;
};

namespace TL
{
	template<typename TList> struct Length;
	template <> struct Length<NullType> 
	{ 
		enum { value = 0 }; 
	};
	template <class T, class U> 
	struct Length< Typelist<T, U> > 
	{ 
		enum { value = 1 + Length<U>::value }; 
	};
	template <class TList, unsigned int index> struct TypeAt;

	template <class Head, class Tail>
	struct TypeAt<Typelist<Head, Tail>, 0> 
	{ 
		typedef Head Result; 
	};
	
	template <class Head, class Tail, unsigned int i> 
	struct TypeAt<Typelist<Head, Tail>, i> 
	{ 
		typedef typename TypeAt<Tail, i - 1>::Result Result;
	};

}

#define TYPELIST_1(T1) Typelist<T1, NullType>
#define TYPELIST_2(T1, T2) Typelist<T1, TYPELIST_1(T2) > 
#define TYPELIST_3(T1, T2, T3) Typelist<T1, TYPELIST_2(T2, T3) >
#define TYPELIST_4(T1, T2, T3, T4) Typelist<T1, TYPELIST_3(T2, T3, T4) 