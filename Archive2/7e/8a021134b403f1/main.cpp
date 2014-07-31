#include <iostream>

class foo {
  friend int main();
  int i = 4;
};

int main() {
  foo obj;
  std::cout << obj.i << std::endl;
}