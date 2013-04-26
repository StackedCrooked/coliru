#include <tuple>
#include <iostream>
#include <type_traits>

template<typename> struct Ignore {};

namespace details {
  struct End {};

  template<typename T, typename... Args>
  struct ignore_filter {
    typedef typename ignore_filter<Args...,T>::type type;
  };

  template<typename T, typename... Args>
  struct ignore_filter<Ignore<T>, Args...> {
    typedef typename ignore_filter<Args...>::type type;
  };

  template<typename... Args>
  struct ignore_filter<End, Args...> {
    typedef std::tuple<Args...> type;
  };
}

template<typename... Args>
struct ignore_filter {
  typedef typename details::ignore_filter<Args..., details::End>::type type;
};


int
main (int argc, char *argv[])
{
  ignore_filter<Ignore<void>, float, int, Ignore<void>, float,float, Ignore<void>>::type foo;

  std::cerr << std::is_same<std::tuple<float,int,float,float>, decltype(foo)>::value;
}