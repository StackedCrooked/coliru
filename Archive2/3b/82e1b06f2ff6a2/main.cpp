#include <iostream>
#include <string>
#include <initializer_list>


class Foo {
    int bar[3];
  public:
    template <typename... Ts>
    Foo(Ts... ts) : bar{ts...} { }
};  


int main() {
  Foo foo({1, 2, 3});
}
