#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <array>

template<int ...I> struct index_tuple_type {
  template<int N> using append = index_tuple_type<I..., N>;
};

template<int N> struct make_index_impl {
  using type = typename make_index_impl<N-1>::type::template append<N-1>;
};

template<> struct make_index_impl<0> { using type = index_tuple_type<>; };

template<int N> using index_tuple = typename make_index_impl<N>::type;

template <typename ...Args>
struct func_traits;

template <int ...I, typename ...Args>
struct func_traits<index_tuple_type<I...>, Args...> {
  template <typename TT, typename FT>
  static inline auto call(TT &&t, FT &&f)
    -> decltype(f(std::get<I>(std::forward<TT>(t))...))
  {
    return f(std::get<I>(std::forward<TT>(t))...);
  }
};

template<
  typename FT,
  typename Arg,
  std::size_t I
>
inline auto explode(std::array<Arg, I>& t, FT &&f)
    -> decltype(func_traits<index_tuple<I>, Arg>::call(t, std::forward<FT>(f)))
{
  return func_traits<index_tuple<I>, Arg>::call(t, std::forward<FT>(f));
}

void foo(int a, int b, int c, int d, int e)
{
    std::cout << a << b << c << d << e << std::endl;
}

int main()
{
    std::array<int, 5> a {1, 2, 3, 4, 5};
    explode(a, foo);
}
