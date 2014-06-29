#include <chrono>
#include <iostream>
#include <type_traits>
#include <utility>
 
// Executes fn with arguments args and returns the time needed
// and the result of f if it is not void
template <class R, class... Args>
auto timer(R (*fn)(Args...), Args... args)
    -> std::pair<double, R> {
  static_assert(!std::is_void<decltype(fn(args...))>::value,
                "Call timer_void if return type is void!");
  auto start = std::chrono::high_resolution_clock::now();
  auto ret = fn(args...);
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed_seconds = end - start;
  return { elapsed_seconds.count(), ret };
}

int main () {
    std::cout << timer([](){return 5;});
    