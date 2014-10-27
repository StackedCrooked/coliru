#include <iostream>
#include <type_traits>

template<bool B, class T= void>
using enable_if_t = typename std::enable_if<B, T>::type;

// ---------------------------------------------------------------------
// ---------------------------------------------------------------------

template<class T, class = enable_if_t<std::is_integral<T> {}>>
using assert_integral_t = T;

template<class T, class = enable_if_t<std::is_floating_point<T> {}>>
using assert_floating_t = T;


template<class T,  int = 0> // (A)
void func (assert_integral_t<T>) { 
  std::cerr << "integral\n";
}

//                 .-- ugly thing to prevent this being
//                 |   treated as a redefinition of (A)
//                 v
template<class T, char = 0>
void func (assert_floating_t<T>) {
  std::cerr << "floating\n";
}

int main () {
  func (123);
  func (1.2f);
  func (3.14);
}