#include <type_traits>

using namespace std;

namespace bar {
  template<typename A>
  struct foo
  {
    static_assert(is_same<A,float>::value || is_same<A,double>::value, "");
    static void set_static_var(A const&x);
    // ...
  };
}

namespace {
  template<typename A>
  struct foo_traits
  {
    // lots of static code supporting the implementation of bar::foo<>
    static A datum;
  };
  template<> float  foo_traits<float>::datum;   // no change if this is in global namespace
  template<> double foo_traits<double>::datum;
  template struct foo_traits<float>;
  template struct foo_traits<double>;
}

template<typename A>
void bar::foo<A>::set_static_var(A const&x)
{
  foo_traits<A>::datum = x;
}
