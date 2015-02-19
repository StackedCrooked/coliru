#include <exception>
#include <iostream>

static int i = 555;
void f() {
  try {
    throw 12;
  } catch (void *) {
    i = 666;
  }
}

void term_handler() {
  std::cout << i << std::endl;
  std::abort();
}

int main() {
  std::set_terminate(term_handler);
  f();
  return 0;
}