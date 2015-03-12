#include <array>
#include <cstddef>
#include <initializer_list>
#include <tuple>
#include <iostream>
#include <type_traits>
#include <utility>

namespace detail {
template <class Tuple, class F, std::size_t...Is>
void tuple_switch(const std::size_t i, Tuple&& t, F&& f, std::index_sequence<Is...>) {
  [](...){}(
    (i == Is && (
       (void)std::forward<F>(f)(std::get<Is>(std::forward<Tuple>(t))), false))...
  );
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
  auto print = [](auto const& i){ std::cout << i << '\n'; };

  {
    auto const t = std::make_tuple(42, 'z', 3.14, 13, 0, "Hello, World!");
  
    for (std::size_t i = 0; i < std::tuple_size<decltype(t)>::value; ++i) {
      tuple_switch(i, t, print);
    }
  }
  
  std::cout << '\n';
  
  {
    auto const t = std::array<int, 4>{{0,1,2,3}};
    for (std::size_t i = 0; i < t.size(); ++i) {
      tuple_switch(i, t, print);
    }
  }
}
