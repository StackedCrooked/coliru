#include <cstddef>
#include <initializer_list>
#include <tuple>
#include <iostream>
#include <type_traits>
#include <utility>

namespace detail {
template <class Tuple, class F, std::size_t...Is>
void tuple_switch(const std::size_t i, Tuple&& t, F&& f, std::index_sequence<Is...>) {
  (void)std::initializer_list<bool>{
    (i == Is && (
       std::forward<F>(f)(std::get<Is>(std::forward<Tuple>(t))), false))...
  };
}
} // namespace detail

template <class Tuple, class F>
void tuple_switch(const std::size_t i, Tuple&& t, F&& f) {
  static constexpr auto N =
    std::tuple_size<std::remove_reference_t<Tuple>>::value;

  detail::tuple_switch(i, std::forward<Tuple>(t), std::forward<F>(f),
                       std::make_index_sequence<N>{});
}

int main() {
  auto const t = std::make_tuple(42, 'z', 3.14, 13, 0, "Hello, World!");
  constexpr std::size_t s =
    std::tuple_size<std::remove_reference_t<decltype(t)>>::value;
  
  for (std::size_t i = 0; i < s; ++i) {
    tuple_switch(i, t, [](auto const& i){ std::cout << i << '\n'; });
  }
}
