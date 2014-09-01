#include <chrono>
#include <iostream>
#include <type_traits>
#include <utility>

// Executes fn with arguments args and returns the time needed
// and the result of f if it is not void
template <class Fn, class... Args>
auto timer(Fn fn, Args... args)
    -> std::pair<double, decltype(fn(args...))> {
  static_assert(!std::is_void<decltype(fn(args...))>::value,
                "Call timer_void if return type is void!");
  auto start = std::chrono::high_resolution_clock::now();
  auto ret = fn(args...);
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed_seconds = end - start;
  return { elapsed_seconds.count(), ret };
}

// If fn returns void, only the time is returned
template <class Fn, class... Args>
double timer_void(Fn fn, Args... args) {
  static_assert(std::is_void<decltype(fn(args...))>::value,
                "Call timer for non void return type");
  auto start = std::chrono::high_resolution_clock::now();
  fn(args...);
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed_seconds = end - start;
  return elapsed_seconds.count();
}

void fun (std::size_t max) {
    int a,b,c;
     for (int i = 0; i < max; i++) {
    a = 1234 + 5678 + i;
    b = 1234 * 5678 + i;
    c=1234/2+i;
   }
}

int main () {
   std::cout << timer_void(fun,2e6) << "\n"
    << timer_void(fun,2e8);
}