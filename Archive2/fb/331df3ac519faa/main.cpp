#include <list>
#include <vector>

// C++11 part
template <typename... T> struct types { using type = types<T...>; };

template <typename P, template <typename> class F> struct transform;

template <
    template <typename...> class C, typename... E,
	template <typename> class F
> struct transform <C <E...>, F> { using type = C <typename F <E>::type...>; };

// C++03 part
namespace container
{
    template <typename T> struct vector { typedef std::vector<T> type; };
    template <typename T> struct list   { typedef std::list<T> type; };
}

template<template <typename> class Container>
struct wrap_into_container
{
	template<typename T>
	struct map
	{
		typedef typename Container<T>::type type;
	};
};

int main ()
{
	typedef types<int, float, int> vec_type;
	typedef transform<vec_type, wrap_into_container<container::vector>::template map>::type wrapped_vec_type;

	wrapped_vec_type::error();
}
