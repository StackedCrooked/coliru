#include <iostream>

void f() {
  try {
    throw 0;
  } catch (void *) {
    std::cout << "Should not see this";
  }
}

int main() { f(); }