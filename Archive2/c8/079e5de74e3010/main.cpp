#include <iostream>
#include <utility>

struct test {
  int val = 10;
};

class Foo {
public:
   test get_value() { return test(); }
};

class Bar {
public:
  using type = decltype(std::declval<Foo>().get_value());
};

int main() {
  Bar::type v;
  std::cout << v.val << std::endl;
}