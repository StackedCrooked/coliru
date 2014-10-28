#include <iostream>
#include <type_traits>

template<bool B, class T= void>
using enable_if_t = typename std::enable_if<B, T>::type;

// ---------------------------------------------------------------------
// ---------------------------------------------------------------------

template<class T, class = enable_if_t<std::is_integral<T> {}>>
struct assert_integral_t {};

template<class T, class = enable_if_t<std::is_floating_point<T> {}>>
struct assert_floating_t {};


template<class T, assert_integral_t<T>* = nullptr>
void func (T) { 
  std::cerr << "integral\n";
}

template<class T, assert_floating_t<T>* = nullptr>
void func (T) {
  std::cerr << "floating\n";
}

int main () {
  func (123);
  func (1.2f);
  func (3.14);
}