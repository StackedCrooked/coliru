#include <iostream>

struct Counter {
  static int Instances;

  Counter() { ++Instances; }
  ~Counter() { --Instances; }
};

int Counter::Instances = 0;

void f() {
  Counter c;
  std::cout << "f(): Instances: " << Counter::Instances << std::endl;
  throw "Exception";
}

int main() {
  std::cout << "Before throw: Instances: " << Counter::Instances << std::endl;
  try {
    f();
  } catch (const char *E) {
    std::cout << "From catch: Instances: " << Counter::Instances << std::endl;
  }

  std::cout << "After catch: Instances: " << Counter::Instances << std::endl;
}