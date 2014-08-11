#include <iostream>
#include <cmath>
#include <array>

template<typename T, typename F, int SIZE, int... N> 
constexpr std::array<T, SIZE> 
genarray(F f) { 
  return std::array<T, SIZE>{{ f(N)... }};
}

template<typename T, typename F, int SIZE, int...> struct recursive_gen;

template<typename T, typename F, int SIZE, int... Args> 
struct recursive_gen<T, F, SIZE, 0, Args...> { 
  static constexpr std::array<T, SIZE> generate(F f) {
    return genarray<T, F, SIZE, 0, Args...>(f);
  }
};

template<typename T, typename F, int SIZE, int N, int... Args> 
struct recursive_gen<T, F, SIZE, N, Args...> {
  static constexpr std::array<T, SIZE> generate(F f) {
    return recursive_gen<T, F, SIZE, N - 1, N, Args...>::generate(f); 
  } 
};

template<typename T, int SIZE>
struct array_generator {
  template<typename F>
  static constexpr std::array<T, SIZE> generate(F f) {
    return recursive_gen<T, F, SIZE, SIZE - 1>::generate(f);
  }
};

std::array<double, 4> const A = array_generator<double, 4>::generate([](int i) { return std::sin(0.1 * i);});
std::array<double, 4> const B = array_generator<double, 4>::generate([](int i) { return std::cos(0.1 * i);});

constexpr int fun(int i) { return 2 * i; } 
constexpr std::array<int, 4> const C = array_generator<int, 4>::generate(fun); // generation during compile time

int main() {
  for(auto i : A) {
    std::cout << i << " ";
  }
  std::cout << std::endl;
  for(auto i : B) {
    std::cout << i << " ";
  }
  std::cout << std::endl;
  for(auto i : C) {
    std::cout << i << " ";
  }
  std::cout << std::endl;
}