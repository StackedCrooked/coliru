#include <iostream>
#include <complex>

int main() {
  std::cout << 5i  << std::endl;
  auto c = std::complex<double>(0,5);
  std::cout<< c <<std::endl;

  c = 5i;
  std::cout<< c <<std::endl;
}