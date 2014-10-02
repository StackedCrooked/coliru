#include <iostream>


void bar(long* foo) {
  for (int i = 0; i != 10; ++i) {
    std::cout << foo[i] << "\n";
  }
}

int main() {
  int* foo = new int[10];
  bar(foo);
}
