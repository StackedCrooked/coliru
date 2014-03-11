#include <iostream>
#include <vector>
#include <map>

using namespace std;

// pack template templates into plain templates

template<template<class> class>
struct Temp1;

template<template<class, class> class>
struct Temp2;

template<template<class, class, class> class>
struct Temp3;

// etc...

// Join (concatenation)

template <typename... P> struct Join_t;
template <typename... P> using  Join = typename Join_t <P...>::type;

template <typename... L, typename... R, typename... P>
struct Join_t <std::tuple<L...>, std::tuple<R...>, P...> :
    Join_t <std::tuple<L..., R...>, P...> { };

template <typename... T>
struct Join_t <std::tuple<T...> > { using type = std::tuple<T...>; };

// generic ContainerTemplate

template<class Temp, typename... T>
struct ContainerTemplate;

// 1 argument

template<template<class> class Container, typename... T>
struct ContainerTemplate <Temp1<Container>, T...>
{
    using container = std::tuple<Container<T>...>;
};

// 2 arguments

template<
	template<class, class> class Container,
	typename T1, typename T2, typename... T
>
struct ContainerTemplate <Temp2<Container>, T1, T2, T...>
{
	using container = Join <
		std::tuple<Container<T1, T2> >,
		typename ContainerTemplate<Temp2<Container>, T...>::container
	>;
};

template<template<class, class> class Container>
struct ContainerTemplate<Temp2<Container> >
{
	using container = std::tuple<>;
};

// etc...

template<class> class Vector { };
template<class, class> class Map { };

int main ()
{
	typename ContainerTemplate<Temp1<Vector>, int, short, char>::container::dummy;

	typename ContainerTemplate<Temp2<Map>, int, int, short, short>::container::dummy;
}
