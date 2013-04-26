#include <iostream>
#include <tuple>
#include <fstream>
#include <type_traits>

struct                             Ignore_Base {}; 
template<typename> struct Ignore : Ignore_Base {}; 

namespace details {
  template<int N, typename T, typename... Args>
  struct ignore_filter {
    typedef typename std::conditional<
      std::is_base_of<Ignore_Base, T>::value,
      typename ignore_filter<N-1,Args...>::type,
      typename ignore_filter<N-1,Args...,T>::type
    >::type type;
  };  

  template<typename... Args>
  struct ignore_filter<1, Ignore<void>, Args...> {
    typedef std::tuple<Args...> type;
  };  
}

template<typename... Args>
struct ignore_filter {
  typedef typename details::ignore_filter<sizeof...(Args), Args...>::type type;
};

int
main (int argc, char *argv[])
{
  ignore_filter<Ignore<void>, float, int, Ignore<void>, int, Ignore<void>>::type foo;


  std::cerr << std::is_same<std::tuple<float,int,int>, decltype(foo)>::value;
}