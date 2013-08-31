#include <tuple>
#include <iostream>
#include <type_traits>

template<typename T> struct Ignore {};

namespace details {
    template<typename T, typename T2> struct tuple_type_cat {};
    template<typename T, typename... Args> struct tuple_type_cat<T, std::tuple<Args...>> {
        typedef std::tuple<T, Args...> type;
    };
    
  template<typename T, typename... Args> struct ignore_filter {
      typedef typename tuple_type_cat<T, typename ignore_filter<Args...>::type>::type type;
  };
  template<typename T, typename... Args> struct ignore_filter<Ignore<T>, Args...> {
      typedef typename ignore_filter<Args...>::type type;
  };
  template<typename T> struct ignore_filter<T> {
      typedef std::tuple<T> type;
  };
  template<typename T> struct ignore_filter<Ignore<T>> {
      typedef std::tuple<> type;
  };
}

template<typename... Args>
struct ignore_filter {
  typedef typename details::ignore_filter<Args...>::type type;
};

int
main (int argc, char *argv[])
{
  ignore_filter<Ignore<void>, float, int, Ignore<void>, float,float, Ignore<void>>::type foo;

  std::cerr << std::is_same<std::tuple<float,int,float,float>, decltype(foo)>::value;
}