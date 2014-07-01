#include <iostream>

struct bar;
struct foo {
  foo() = default;
  foo(bar &b) { std::cout << "made a foo from a bar" << std::endl; }
  
  bar operator++(int);
};

struct bar {
  bar() = default;
  bar(foo &f) { std::cout << "made a bar from a foo" << std::endl; }
  foo operator++(int) {
    return foo(*this);
  }
};

bar foo::operator++(int) {
  return bar(*this);
}

int main() {
  foo f;  
  f++++++;
}