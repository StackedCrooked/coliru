#include <tuple>
#include <type_traits>

template<typename T> class CRTPBase;

template<template<typename, typename...> class TT,
    typename SENDER, typename... ARGS>
class CRTPBase<TT<SENDER, ARGS...>>
{
    using type = std::tuple<SENDER, ARGS...>;
};

template<typename SENDER , typename... ARGS>
class event : public CRTPBase<event<SENDER,ARGS...>>
{
    // ...
};

struct X { };

int main()
{
    event<X, int, double> e;

    // This assertion will not fire!
    static_assert(std::is_same<
        decltype(e)::type,
        std::tuple<X, int, double>
        >::value, "!");
}