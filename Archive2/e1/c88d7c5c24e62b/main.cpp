// author: filip.roseen@gmail.com
//     SO: http://stackoverflow.com/users/1090079

#include <type_traits>

template<int N>
using ic__ = std::integral_constant<int, N>;

template<class D, int N = 16>
struct counter_impl : counter_impl<D, N-1> {
#pragma GCC diagnostic ignored "-Wnon-template-friend"
  friend constexpr int check (D, ic__<N>);
#pragma GCC diagnostic pop
};

template<class D>
struct counter_impl<D, -1> { };

template<class T, int N = 0>
struct counter_impl_helper : counter_impl<T> {
  friend constexpr int check (T, ic__<N>) { return 1; }
};

template<class T>
struct count_tag : counter_impl<count_tag<T>> {
  constexpr count_tag () = default;
};

#define refp_count(X) (/* TODO: BST */ \
  noexcept(check(X{}, ic__<  0>{})) + \
  noexcept(check(X{}, ic__<  1>{})) + \
  noexcept(check(X{}, ic__<  2>{})) + \
  noexcept(check(X{}, ic__<  3>{})) + \
  noexcept(check(X{}, ic__<  4>{})) + \
  noexcept(check(X{}, ic__<  5>{})) + \
  noexcept(check(X{}, ic__<  6>{})) + \
  noexcept(check(X{}, ic__<  7>{})) + \
  noexcept(check(X{}, ic__<  8>{})) + \
  noexcept(check(X{}, ic__<  9>{})) + \
  noexcept(check(X{}, ic__< 10>{})) + \
  noexcept(check(X{}, ic__< 11>{})) + \
  noexcept(check(X{}, ic__< 12>{})) + \
  noexcept(check(X{}, ic__< 13>{})) + \
  noexcept(check(X{}, ic__< 14>{})) + \
  noexcept(check(X{}, ic__< 15>{})) + \
  noexcept(check(X{}, ic__< 16>{})) + \
  /*             ...               */ \
0)

#define refp_incr(X) (counter_impl_helper<X, refp_count(X) >{}, refp_count (X))
