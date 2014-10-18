#include <memory>
#include <utility>

struct objectA {};
struct objectB {};

std::pair<objectA*,objectB*> func();
std::tuple<objectA*,objectB*,objectA*> func2();

template<class A>
struct as_unique{using type=A;};
template<class A>
struct as_unique<A*>{using type=std::unique_ptr<A>;};
template<class A>
using as_unique_t=typename as_unique<A>::type;

template<template <class...> class Tuple, class...Ts, class U, std::size_t...Is>
Tuple<Ts...> tuple_cast(std::index_sequence<Is...>, U&& u){
  return Tuple<Ts...>{static_cast<Ts>(std::get<Is>(std::forward<U>(u)))...};
}

template<class...Ts, template<class...> class Tuple>
Tuple<as_unique_t<Ts>...> take_ownership(Tuple<Ts...>&& t){
  return tuple_cast<Tuple, as_unique_t<Ts>...>(std::index_sequence_for<Ts...>{}, std::move(t));
}

int main() {
    auto p = take_ownership(func());
    auto q = take_ownership(func2());
}
