template <int N> struct require_constexpr { };
struct test { 
  constexpr test() = default;
  //constexpr test(const test &){ }
  //constexpr test(const test &) = default;
};

template <typename T> constexpr int foo (T ) { return 0; }
template <typename T> constexpr int bar (T obj) { return foo(require_constexpr< foo(obj) > { }); }

int main ()
{
  constexpr auto const ar = test();
  constexpr auto const baz = require_constexpr< bar(ar) >();
  
  (void) baz;
  return 0;
}