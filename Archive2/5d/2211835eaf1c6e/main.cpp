#include <iostream>
#include <vector>
#include <map>

using namespace std;

template<template<class... > class Container, typename P>
struct Embed_t;

template<template<class... > class Container, typename... T>
struct Embed_t <Container, std::tuple <T...> >
{
    using type = Container <T...>;
};

template<template<class... > class Container, typename P>
using Embed = typename Embed_t <Container, P>::type;

template<template<class... > class Container, typename... P>
struct ContainerTemplate
{
    using container = std::tuple<Embed <Container, P>...>;
};

int main ()
{
	typename ContainerTemplate<std::vector, std::tuple<int>, std::tuple<short>, std::tuple<char> >::container::dummy;

	typename ContainerTemplate<std::map, std::tuple<int, int>, std::tuple<short, short> >::container::dummy;
}
