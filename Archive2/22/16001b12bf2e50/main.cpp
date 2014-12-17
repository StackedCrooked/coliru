#include <iostream>
#include <string>
#include <functional>

using namespace std;

#define LOG_DEBUG 1

template< class T, bool dbg = LOG_DEBUG, std::enable_if_t<dbg>* = nullptr >
inline void print(T && t) 
   { cout << "EXPENSIVE PRINT " << std::forward<T>(t) << std::endl; }
  
template< class T, bool dbg = LOG_DEBUG, std::enable_if_t<dbg>* = nullptr >
inline void print_function(T && t) 
   { cout << "CHEAP PRINT " << std::forward<T>(t)() << std::endl; }

template< class T, bool dbg = LOG_DEBUG, std::enable_if_t<!dbg>* = nullptr >
inline void print(T && ) {}
  
template< class T, bool dbg = LOG_DEBUG, std::enable_if_t<!dbg>* = nullptr >
inline void print_function(T && ) {}

int int_generator() {
    return 42;
}

int main(void) {
  print_function([] { int i = 0; /* do expensive computation */ i = int_generator(); return i; });
  print(52);
  print(int_generator());
  return 0;
}