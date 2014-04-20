#include <array>

template <int...I>
struct indices {};
template <int N, int...I>
struct make_indices : make_indices<N-1, N-1, I...> {};
template <int...I>
struct make_indices<0, I...> : indices<I...> {};

template <typename T, int...I>
constexpr std::array<T, sizeof...(I)> iota_array_(indices<I...>) {
  return {I...};
}

template <typename T, std::size_t N>
constexpr std::array<T, N> iota_array() {
  return iota_array_<T>(make_indices<N>());
}

const unsigned E = 256;

class A {
    public:
        static const std::array<unsigned, E> x;
    // ...
};

const std::array<unsigned, E> A::x = iota_array<unsigned, E>();

#include <iostream>

int main() {
  auto counter = 0;
  for (auto&& i : A::x) {
    if (counter == 32) {
      counter = 0;
      std::cout << '\n';
    } else {
      std::cout << ' ';
      ++counter;
    }
    std::cout << i;
  }
  std::cout << '\n';
}
