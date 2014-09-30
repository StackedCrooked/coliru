#include <iostream>
#include <type_traits>
#include <utility>

template <typename F, typename A,
          typename R = decltype(std::declval<F &>()(std::declval<A &>())),
          typename FF = decltype(
              static_cast<R (*)(A &)>(F::operator())(std::declval<const A &>()))>
std::true_type test(int);
template <typename F, typename A> std::false_type test(...);
template <typename F, typename A>
using is_function_argument_immutable = decltype(test<F, A>(1));

template <typename F>
std::enable_if_t<is_function_argument_immutable<F, int>::value, void> foo(F f)
{
  const int x = 1;
  f(x);
  std::cout << x << "\n";
}

template <typename F>
std::enable_if_t<!is_function_argument_immutable<F, int>::value, void> foo(F f)
{
  int x = 1;
  f(x);
  std::cout << x << "\n";
}

int main()
{
  foo([](auto &x) { x += 1; });
  foo([](const auto &) { });
  return 0;
}