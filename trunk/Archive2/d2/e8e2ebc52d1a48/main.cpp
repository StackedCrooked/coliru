#include <iostream>
#include <typeinfo>

int main() {
  auto p1 = new float[5][5];
  std::cout << typeid(p1).name() << std::endl;
  std::cout << typeid(float**).name() << std::endl;
  float* p[5];
  std::cout << typeid(decltype(p)).name() << std::endl;  
}