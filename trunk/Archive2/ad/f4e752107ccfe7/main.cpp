#include <iostream>
#include <cmath>
#include <cstdio>
#include <ctime>
#include <typeinfo>

struct X {
};

template<typename WrappedType>
struct Y {
  WrappedType * next;
  int x;
};

template <typename WrappedType>
struct Z {
    WrappedType * next;
};

template<typename...>
struct has_Y : std::false_type { };

template<template<typename> class Wrapper, typename Wrapped>
struct has_Y<Wrapper<Wrapped>> : has_Y<Wrapped> { };

template<typename Wrapped>
struct has_Y<Y<Wrapped>> : std::true_type { };


namespace impl {
  template<typename _>
  int& get_x_ (Y<_> * val) { return val->x; }

  template<typename T>
  int& get_x_ (T    * val) { return get_x_ (val->next); }

  // --------------------------------------------------
  template<typename T>
  T * add_x (T * t, decltype (get_x (t), int { })) {
    return t;
  }

  template<typename T>
  Y<T> * add_x (T * t, ...) {
    return { new Y<T> };
  }
}

template<typename T, typename std::enable_if<has_Y<T>::value>::type * = nullptr>
auto get_x (T * t) -> decltype (impl::get_x_ (t)) 
{
  return impl::get_x_ (t);
}

template<typename T>
auto add_x (T * val) -> decltype (impl::add_x (val, 0))
{
  return impl::add_x (val, 0);
}

int
main (int argc, char *argv [])
{
  {
    auto a = new Y<X>; a->x = 10;
    auto b = new Z<Z<Y<X>>>;
    b->next = new Z<Y<X>>;
    b->next->next = new Y<X>;
    b->next->next->x = 20;

    std::cout << get_x (a) << std::endl;
    std::cout << get_x (b) << std::endl;
  }

  {   
    auto a = new Z<X>;
    auto b = new Y<Z<X>>;
    get_x(b) = 1;

    auto a2 = add_x(a);
    auto b2 = add_x(b);

    get_x(a2) = 2;
    get_x(b2) = 3;

    std::cout << get_x(b) << " " << get_x(a2) << " " << get_x(b2) << std::endl;
    // should print 3 2 3
  }

  return 0;
}