#include <iostream>

int main() {
  int x = 12;
  [i = x + 1] { std::cout << i << std::endl; }();
}