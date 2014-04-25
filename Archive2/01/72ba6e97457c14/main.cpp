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

// change 0 to 1 to make it compile correctly!
#if 0
  template<> struct foo_traits<float>
  {
    static float datum;
  };
  
  template<> struct foo_traits<double>
  {
    static double datum;
  };  
#endif

  float  foo_traits<float>::datum;   // no change if this is in global namespace
  double foo_traits<double>::datum;
}

namespace bar {
  template<typename A>
  void foo<A>::set_static_var(A const&x)
  {
    foo_traits<A>::datum = x;
  }
}

int main() {
    bar::foo<float>::set_static_var(3.14f);
    bar::foo<double>::set_static_var(42);
}
