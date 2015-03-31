#pragma once
//Typelist Modern C++ Design Chapter 3

class NullType{};

template< typename T, typename U> 
struct Typelist 
{
	typedef T Head;
	typedef U Tail;
};

//Typelist Algorithms
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

	template<class TList,class T> struct IndexOf;

	template<class T> 
	struct IndexOf<NullType,T>
	{
		enum
		{
			value=-1,
		};
	};

	template <class T, class Tail>
	struct IndexOf<Typelist<T, Tail>, T>
	{
		enum {
			value = 0
		};
	};
	
	template <class Head, class Tail, class T> 
	struct IndexOf<Typelist<Head, Tail>, T> 
	{
	private:   
		enum 
		{ 
			temp = IndexOf<Tail, T>::value 
		}; 
	public:   
		enum 
		{ 
			value = temp == -1 ? -1 : 1 + temp 
		}; 
	};
}

//Typelist macro for linear creation
#define TYPELIST_1(T1) Typelist<T1, NullType>
#define TYPELIST_2(T1, T2) Typelist<T1, TYPELIST_1(T2) > 
#define TYPELIST_3(T1, T2, T3) Typelist<T1, TYPELIST_2(T2, T3) >
#define TYPELIST_4(T1, T2, T3, T4) Typelist<T1, TYPELIST_3(T2, T3, T4) 