#include <iostream>
#include <cmath>
#include <cstdio>
#include <ctime>
#include <typeinfo>

struct X {
    int a;
};

template<typename Base>
struct Y {
  Base* base;
  int x;
};

template <typename Base>
struct Z {
    Base* base;
};


template<typename...>
struct has_Y : std::false_type { };

template<template<typename> class Wrapper, typename Base>
struct has_Y<Wrapper<Base>> : has_Y<Base> { };

template<typename Base>
struct has_Y<Y<Base>> : std::true_type { };


template <typename...>
struct has_A : std::false_type { };

template <template<typename> class Wrapper, typename Base>
struct has_A<Wrapper<Base>> : has_A<Base> { };

template <>
struct has_A<X> : std::true_type { };


namespace impl {
      
  template<typename _>
  int& get_x_(Y<_>* val) { return val->x; }
  
  template<typename T>
  int& get_x_(T* val) { return get_x_(val->base); }

    
  template <typename T>
  int& get_a_(T* val) { return get_a_(val->base); }
  
  template <>
  int& get_a_(X* val) { return val->a; }


  // --------------------------------------------------
  template<typename T>
  T* add_x(T* t, decltype(get_x(t), int{})) {
    return t;
  }

  template<typename T>
  Y<T>* add_x (T* t, ...) {
    return { new Y<T> };
  }
}

template<typename T, typename std::enable_if<has_Y<T>::value>::type* = nullptr>
auto get_x(T* t) -> decltype(impl::get_x_(t)) 
{
  return impl::get_x_(t);
}

template<typename T>
auto add_x(T* val) -> decltype (impl::add_x(val, 0))
{
  return impl::add_x(val, 0);
}

template <typename T, typename std::enable_if<has_A<T>::value>::type* = nullptr>
auto get_a(T* t) -> decltype(impl::get_a_(t))
{
    return impl::get_a_(t);
}

int
main (int argc, char *argv [])
{
  {   
    auto a = new Z<X>;
    auto b = new Y<Z<X>>;
    auto c = new Z<Y<Z<X>>>; c->base = new Y<Z<X>>;
    get_x(b) = 1;
    get_x(c) = 4;

    auto a2 = add_x(a);
    auto b2 = add_x(b);
    auto c2 = add_x(c);

    get_x(a2) = 2;
    get_x(b2) = 3;
    get_x(c2) = 5;

    std::cout << get_x(b) << " " << get_x(a2) << " " << get_x(b2) << " " << get_x(c) << " " << get_x(c2) << std::endl;
    // should print 3 2 3 5 5
    
    auto x = new X;
    auto y = new Y<X>; y->base = new X;
    std::cout << get_a(x) << std::endl;
    std::cout << get_a(y) << std::endl;
  }

  return 0;
}