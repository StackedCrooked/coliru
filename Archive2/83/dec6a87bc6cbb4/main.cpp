#include <random>
#include <unordered_set>
#include <numeric>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <tuple>
#include <type_traits>
#include <utility>

// Executes fn with arguments args and returns the time needed
// and the result of f if it is not void
template <class Fn, class... Args>
auto timer(Fn fn, Args &&... args)
    -> typename std::enable_if<
          !std::is_void<
               decltype(fn(std::forward<Args>(args)...))>::value,
          std::pair<double, decltype(fn(std::forward<Args>(
                                 args)...))> >::type {

  auto start = std::chrono::high_resolution_clock::now();
  auto ret = fn(std::forward<Args>(args)...);
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed_seconds = end - start;
  return {elapsed_seconds.count(), ret};
}

// If fn returns void, only the time is returned
template <class Fn, class... Args>
auto timer(Fn fn, Args &&... args)
    -> typename std::enable_if<std::is_void<decltype(fn(std::forward<
                                   Args>(args)...))>::value,
                               std::tuple<double> >::type {

  auto start = std::chrono::high_resolution_clock::now();
  fn(std::forward<Args>(args)...);
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed_seconds = end - start;
  return std::make_tuple(elapsed_seconds.count());
}


auto random_numbers_set (std::size_t how_many, int max) {
    std::unordered_set<int> ret;
	std::mt19937 en {std::random_device{}()};
	std::uniform_int_distribution<> dis (0,max);
	while (ret.size() < how_many)
		ret.insert(dis(en));
  return ret;
}

auto  random_numbers_vector (std::size_t how_many, int max) {
	std::vector<int> ret(max);
  std::iota(ret.begin(),ret.end(),0);
std::mt19937 en {std::random_device{}()};
  std::shuffle(ret.begin(),ret.end(),en);
  ret.erase(ret.begin() + how_many, ret.end());
  return ret;
}

int main () {
  std::cout << timer(random_numbers_set,100000000,1000000000).first  << "\n"
    << timer(random_numbers_vector,100000000,1000000000).first << "\n";
}