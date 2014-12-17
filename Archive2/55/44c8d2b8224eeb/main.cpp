#include <iostream>
#include <string>
#include <functional>

using namespace std;

#define LOG_DEBUG 1

template <bool>
struct Log;

template <>
struct Log<true> {
  template< class T >
  static void print(T && f) {
     cout << "EXPENSIVE PRINT " << f << std::endl;
  }
  
  template< class T >
  static void print_function(T && f) {
      cout << "CHEAP PRINT " << f() << std::endl;
  }
};

template <>
struct Log<false> {
  template< class T >
  static void print(T f) {}
  
  template< class T >
  static void print_function(std::function<T> f) {}
};

#ifdef LOG_DEBUG
using LOG = Log<true>;
#else
using LOG = Log<false>;
#endif

int int_generator() {
    return 42;
}

int main(void) {
  LOG::print_function([] { int i = 0; /* do expensive computation */ i = int_generator(); return i; });
  LOG::print(52);
  LOG::print(int_generator());
  return 0;
}