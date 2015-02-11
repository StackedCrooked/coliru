#include <iostream>
#include <type_traits>
#include <array>
#include <utility>

template <class F, class Tuple, std::size_t... I>
constexpr decltype(auto) apply_impl( F&& f, Tuple&& t, std::index_sequence<I...> )
{
  return std::forward<F>(f)(std::get<I>(std::forward<Tuple>(t))...);
}
 
template <class F, class Tuple>
constexpr decltype(auto) apply(F&& f, Tuple&& t)
{
    return apply_impl(std::forward<F>(f), std::forward<Tuple>(t),
        std::make_index_sequence<std::tuple_size<std::decay_t<Tuple>>{}>{});
}

void test(int a, int b, int c)
{
    std::cout << a << " : " << b << " : " << c << std::endl;
}

int main()
{
    std::array<int,3> foo{1, 2, 3};
    apply(test, foo);
}