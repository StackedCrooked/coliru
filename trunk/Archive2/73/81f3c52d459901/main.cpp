#include <iostream>
#include <type_traits>

template<typename T>
void foo(T &&a) {
  std::cout << std::boolalpha << std::is_rvalue_reference<decltype(a)>::value << std::endl;
}

struct O { };

auto main() -> int {
  O o;
  foo(o); //T is deduced to o&,a is O&
  foo(std::move(o)); //T is deduced to O,a is O&&   

  return 0;
}