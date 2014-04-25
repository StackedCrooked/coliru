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
  template<> float  foo_traits<float>::datum = 0;
  template<> double foo_traits<double>::datum = 0;
  template struct foo_traits<float>;
  template struct foo_traits<double>;
}

namespace bar {
  template<typename A>
  void foo<A>::set_static_var(A const&x)
  {
    foo_traits<A>::datum = x;
  }
  template struct foo<double>;     // error only appears if these lines are present.
  template struct foo<float>;      // but without these lines, the whole file is void.
}

int main() {
    bar::foo<float>::set_static_var(3.14f);
    bar::foo<double>::set_static_var(42);
}
