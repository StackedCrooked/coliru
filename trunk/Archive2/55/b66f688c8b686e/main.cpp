#include <chrono>
#include <random>
#include <iostream>
#include <type_traits>

template<typename T>
typename std::enable_if<std::is_floating_point<T>::value, T>::type randNumBetween(T lower, T upper, std::default_random_engine &gnr) {
  if(lower > upper) std::swap(lower, upper);
  std::uniform_real_distribution<T> distribution(lower, upper);
  return distribution(gnr);
}

template<typename T>
typename std::enable_if<std::is_integral<T>::value, T>::type randNumBetween(T lower, T upper, std::default_random_engine &gnr) {
  if(lower > upper) std::swap(lower, upper);
  std::uniform_int_distribution<T> distribution(lower, upper);
  return distribution(gnr);
}

int main() {
  auto seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::default_random_engine gnr(seed);
  for(auto i(0); i < 10; ++i) std::cout << randNumBetween(10, 20, gnr) << std::endl;
  for(auto i(0); i < 10; ++i) std::cout << randNumBetween(10.0, 20.0, gnr) << std::endl;
  return 0;
}