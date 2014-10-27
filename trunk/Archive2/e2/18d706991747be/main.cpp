#include <chrono>
#include <tuple>
#include <type_traits>
#include <utility>

#include <iostream>

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

int fun (int,double) {return 7;}
int fun (int,int) {return 3;}

int main () {
    
    // Contains the runtime in first component and return value in second if not void
    auto timed = timer([](auto i, auto d){return fun(i,d);},1,3);
    std::cout << "Took " << std::get<0>(timed)          // We do not need to know if fun returns void to do get<0> 
        << " seconds, returned " << std::get<1>(timed); // Only get<1> if fun does not return void
}
