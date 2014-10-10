#include <iostream>

struct Statistics {
    int counter1;
    int counter2;
    int counter3;
};

int main () {
  Statistics foo;
  std::cout << foo.counter1 << ", " << foo.counter2 << ", " << foo.counter3 << std::endl;
  Statistics bar = {0};
  std::cout << bar.counter1 << ", " << bar.counter2 << ", " << bar.counter3 << std::endl;
}