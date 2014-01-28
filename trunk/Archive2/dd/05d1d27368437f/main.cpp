#include <tuple>
#include <iostream>
#include <functional>
#include <stdexcept>
#include <type_traits>

template<int ...> struct seq {};

template<int N, int ...S> struct gens : gens<N-1, N-1, S...> {};

template<int ...S> struct gens<0, S...>{ typedef seq<S...> type; };

template <typename R, typename Tp, typename ...FArgs> 
struct t_app_aux {
  template<int ...S>
  R static callFunc(std::function<R (FArgs...)> f,Tp t,seq<S...>) {
    return f(std::get<S>(t) ...);
  }
};

template <typename R, typename Tp, typename ...FArgs>
auto t_app(std::function<R (FArgs...)> f, Tp t)
    -> typename std::enable_if<std::tuple_size<Tp>::value == sizeof...(FArgs), R>::type {
//  static_assert(std::tuple_size<Tp>::value == sizeof...(FArgs), "type error: t_app wrong arity"); //wrong size generates a compile error, how about runtime check?
  return t_app_aux<R, Tp, FArgs...>::callFunc(f,t,typename gens<sizeof...(FArgs)>::type());
}

template <typename R, typename Tp, typename ...FArgs>
auto t_app(std::function<R (FArgs...)>, Tp)
    -> typename std::enable_if<std::tuple_size<Tp>::value != sizeof...(FArgs), R>::type {
  throw std::runtime_error("type error: t_app wrong arity");
}

int main(void)
{
    {
      std::tuple<int, float, double> t = std::make_tuple(1, 1.2, 5);
      std::function<double (int,float,double)> foo = [](int x, float y, double z) {
        return x + y + z;
      };
      std::cout <<  t_app(foo,t) << std::endl;
    }
    {
      std::tuple<int, float> t = std::make_tuple(1, 1.2);
      std::function<double (int,float,double)> foo = [](int x, float y, double z) {
        return x + y + z;
      };
      std::cout <<  t_app(foo,t) << std::endl;
    }
}
