#include <functional>
#include <iostream>

void f(int a, int b, int c) {
  std::cout << a << " " << b << " " << c << std::endl;
}

int main() {
  auto f1 = std::bind(f, 1, _1, _2);
  
  //f1(2,3);
  
  return 0;
}
