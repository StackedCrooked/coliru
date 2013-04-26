#include <iostream>
#include <tuple>

template<size_t N, typename T1, typename... Rest>
struct FooBar {
  typedef typename FooBar<N-1, T1, T1, Rest...>::tuple_type tuple_type;
};

template<typename T, typename... Rest>
struct FooBar<0, T, Rest...> {
  typedef std::tuple<Rest...> tuple_type;
};

int
main (int argc, char *argv[])
{
  std::cerr << std::tuple_size<
      typename FooBar<10,int>::tuple_type
  >::value  << " ";
}