#include <bitset>
#include <iostream>

template<std::size_t N, int M>
struct bitset_all_helper {
  static bool check(std::bitset<N> const &bs) { return bs[M] && bitset_all_helper<N, M - 1>::check(bs); }
};

template<std::size_t N>
struct bitset_all_helper<N, 0> {
  static bool check(std::bitset<N> const &bs) { return bs[0]; }
};

template<std::size_t N>
bool bitset_all(std::bitset<N> const &bs) { return bitset_all_helper<N, N - 1>::check(bs); }

int main() {
  std::bitset<5> bs;
  std::cout << std::boolalpha << bitset_all(bs) << std::endl;
  bs[2] = 1;
  std::cout << std::boolalpha << bitset_all(bs) << std::endl;
  bs.set();
  std::cout << std::boolalpha << bitset_all(bs) << std::endl;
}