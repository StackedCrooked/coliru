#include <iostream>
#include <type_traits>
#include <string.h>

/*
  bool SmartEquals(double expected, double actual) {
    double diff = expected - actual;
    diff = diff > 0.0 ? diff : -diff;
    return diff > 0.001;
  }
*/

  template <typename T>
  bool SmartEquals(const T& expected, const T& actual,
                   decltype(expected == actual)* = 0) {  // Enable iff there's operator=
    return expected == actual;
  }

  template <typename T, typename ... Ignore>
  bool SmartEquals(const T& expected, const T& actual,
                   const Ignore& ...,
                   typename std::enable_if<std::is_pod<T>::value>::type* = 0
                   ) {
    return memcmp(std::addressof(expected), std::addressof(actual), sizeof(T)) == 0;
  }

  enum Fruit { Orange };
  struct Apple { int x; Fruit fruit; };
  
  template <typename T, typename T2>
  void PrintEquality(const T& a, const T2& b) {
      std::cout << SmartEquals(a, b) << std::endl;
  }

int main() {
    Apple app = {1, Orange};
    Apple app2 = {1, Orange};
    
    bool True = true;
    bool True2 = true;
    
    PrintEquality(app, app2);
    PrintEquality(True, True2);
    
    return 0;
}