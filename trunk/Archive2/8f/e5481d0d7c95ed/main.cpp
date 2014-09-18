#include <iostream>
#include <string>
#include <vector>

template<int t>
struct Printer : Printer<t-1> {
  Printer() {
    std::cout << t << std::endl;
  }
};

template<>
struct Printer<0> {
};

int main() {
  Printer<10>();
};
  