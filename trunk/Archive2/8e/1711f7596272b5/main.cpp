#include <cstdio>
#include <utility>
#include <array>

template<typename FT, typename Arg, std::size_t I, int... Is>
auto explode_impl(std::array<Arg, I>& t, FT &&f, std::integer_sequence<int, Is...>) {
  return (std::forward<FT>(f))(std::get<Is>(t)...);
}

template<typename FT, typename Arg, std::size_t I>
auto explode(std::array<Arg, I>& t, FT &&f) {
  return explode_impl(t, f, std::make_integer_sequence<int, I>{});
}

void test2(int i1, int i2) {
  printf("%d %d\n", i1, i2);
}

int main() {
  std::array<int, 2> t{1, 2};
  explode(t, test2);
}