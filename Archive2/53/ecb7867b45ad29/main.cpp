#include <iostream>
#include <utility>

template<class...>struct voider { using type=void; };
template<class...Ts>using void_t=typename voider<Ts...>::type;

template<class...>struct types{ using type=types; };

namespace details {
  template<template<class...>class Z, class types, class=void>
  struct can_apply : std::false_type {};
  template<template<class...>class Z, class...Ts>
  struct can_apply<Z, types<Ts...>, void_t< Z<Ts...> > >:
    std::true_type
  {};
}

template<template<class...>class Z, class...Ts>
using can_apply_t = details::can_apply<Z, types<Ts...>>;

#define CALL_METHOD_RESULT(Name, Method) \
template<class Sig, class=void> \
struct Name {}; \
template<class C, class...Ts> \
struct Name< C(Ts...), void_t< \
  decltype( std::declval<C>().Method(std::declval<Ts>()...) ) \
>> { \
  using type = decltype( std::declval<C>().Method(std::declval<Ts>()...) ); \
}; \
template<class Sig> \
using Name ## _t = typename Name< Sig >::type

#define CAN_CALL_METHOD( Method ) \
CALL_METHOD_RESULT( call_ ## Method, Method ); \
template<class Sig> \
using can_call_ ## Method = can_apply_t< call_ ## Method ## _t, Sig >


/// Forward to function Name, if is exists.
#define FORWARD(Name, Method, Target, target) \
  template <class... Args> \
  auto Name(Args&&... args) \
  -> call_ ## Method ## _t<Target(Args...)> \
  { \
    return target.Method(std::forward<Args>(args)...); \
  } \
  template <class...Args> \
  std::enable_if_t<!can_call_ ## Method <Target(Args...)>{}> \
  Name ( Args&&...) = delete

#define DEFINE(Name) \
  CAN_CALL_METHOD(Name); \
  FORWARD(Name, Name, Base, base)


template <typename Base>
struct wrapper
{
  Base base;
  DEFINE(foo);
  DEFINE(bar);
};


#define PING()                                  \
  std::cerr << __PRETTY_FUNCTION__ << '\n'
struct foo_no_bar
{
  void foo(int)           const { PING(); }
  int foo(double)         const { PING(); return 1; }
  int foo(double, double) const { PING(); return 1; }
};

struct foo_and_bar
{
  void foo() const { PING(); }
  void bar()       { PING(); }
};

int main()
{
  wrapper<foo_and_bar> f;
  f.foo();
  f.bar();
  wrapper<foo_no_bar> b;
  b.foo(1);
  b.foo(1.0);
  b.foo(1.0, 2.0);
  // b.foo(1,2,3); // -- does not compile
}
