#include <iostream>
#include <type_traits>

struct WithFunc {};

template<typename T,             typename... Ts> struct has            : std::false_type {};
template<typename T,             typename... Ts> struct has<T,T,Ts...> : std::true_type {};
template<typename T, typename U, typename... Ts> struct has<T,U,Ts...> : has<T,Ts...> {};

template<typename... Tags>
struct Obj {
  template<
    typename hack = int,
    typename std::enable_if<has<WithFunc, Tags..., hack>::value>::type * = nullptr
  > void func () {}
};


int
main (int argc, char *argv[])
{
  Obj<WithFunc> {}.func ();
  Obj<>         {}.func (); // illegal
}