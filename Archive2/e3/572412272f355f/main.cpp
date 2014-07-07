#include <iostream>

template <typename Fn>
void foo(Fn F, int &j) {
  std::cout << "Calling outer" << std::endl;
  auto Inner = F();
  j = 4242;
  std::cout << "Calling inner" << std::endl;
  Inner();
}

int main () {
  int i = 10, j = 12;
  
  auto fn = [i, &j]() mutable {
    j = 1000;
    auto inner = [i, &j]() mutable {
      std::cout << "inner i = " << i << ", inner j = " << j << std::endl;
      j = 100;    
    };
    std::cout << "outer i = " << i << ", outer j = " << j << std::endl;
    i = 200;
    return inner;
  };
  foo(fn, j);
  std::cout << "main j = " << j << std::endl;
}