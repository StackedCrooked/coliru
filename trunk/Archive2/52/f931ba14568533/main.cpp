#include <iostream>
#include <type_traits>

enum Foo {
  A = 3,
  B = 4
};

template<Foo T> class Bar {
  const Foo foo_;

public:

  Bar() : foo_(T) {}

  template<Foo U = T, typename = typename std::enable_if<U == A>::type>
  Bar(int, int, int) : foo_(T) {}


  template<Foo U = T, typename = typename std::enable_if<U == B>::type>
  Bar(int x, int y, int z, int w) : foo_(T) {}

  ~Bar() {}

};

int main()
{
  //Bar<A> a1(1,2,3); // compiles
  //Bar<A> a2(1,2,3,4); // ERROR
  //Bar<B> b1(1,2,3,4); // compiles
  //Bar<B> b2(1,2,3); // ERROR

  return 0;
}