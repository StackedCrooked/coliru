#include <iostream>

#include <type_traits>
#include <memory>

struct Testing {
  std::aligned_union</*Len*/0, int, float, double>::type storage_;
};

int main() {
  Testing t;
  std::cout << "Hello\n";
  return 0;
}
