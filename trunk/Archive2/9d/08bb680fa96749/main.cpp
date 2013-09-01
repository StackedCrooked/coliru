#include <type_traits>
#include <utility>
#include <iostream>

int func_1(int a) {
  return a + 3;
}

int func_2(int& b) {
  b = 14;
  return 6;
}

// BOOST_FWD_REF expand to const Arg& for compilers without c++11 rvalue
template <class Ret, class Arg>
Ret eval(Ret(*func)(Arg), const Arg& arg) {
  return func(arg);
}

int main() {
  int a = 3;
  std::cout << eval(func_1, a) << std::endl; // ok
  //std::cout << eval(func_2, a) << std::endl; // error
  //std::cout << eval(func_2, std::ref(a)) << std::endl; // error
  return 0;
}
