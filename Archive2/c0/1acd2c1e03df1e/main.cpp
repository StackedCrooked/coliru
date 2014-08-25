#include <iostream>
#include <array>

template<
  typename T,
  template < typename >
  class Container
> struct Foo{
  void test() const {
    std::cout << "Unspecialized Foo" << std::endl;
  }
};

template< size_t N >
struct array_{
  template< typename T >
  using policy = std::array<T, N>;
};

template<
  typename T, size_t N
> struct Foo< T, array_<N>::template policy >{
  void test() const {
    std::cout << "Foo< T, array<" << N << ">::policy >" << std::endl;
  }
};

int main()
{
    Foo< int, array_<10>::template policy > foo;
    foo.test();
    return 0;
}