#include <cstddef>
#include <cstdint>
#include <cstring>
#include <cstdio>
#include <tuple>
#include <utility>
#include <iostream>
#include <type_traits>

template<typename F, typename T, size_t...Idx>
void doit(F f, T&& t, std::index_sequence<Idx...>) {
  // C++17
  // (... , f(std::get<Idx>(std::forward<T>(t))));
  // C++14 workaround
  const auto _ = { (f(std::get<Idx>(std::forward<T>(t))), 0)... };
  (void)_;
}

template<typename F, typename T>
void tuple_for(T && t, F f) {
  using size_type = std::tuple_size<typename std::decay<T>::type>;
  doit(f, std::forward<T>(t), std::make_index_sequence<size_type::value>());
}

int main() {
    auto t = std::make_tuple(1, "2ABC", 3.5);
    tuple_for(t, [](auto&& x) {
        std::cout << x << std::endl;
    });
}
