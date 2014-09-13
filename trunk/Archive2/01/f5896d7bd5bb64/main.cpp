#include <iostream>
#include <string>
#include <algorithm>

struct Foo {
    static char const *arr[];
};

char const *Foo::arr[] = {"ace_hearts", "2_hearts", "3_hearts"};

int main() {
  std::for_each(std::begin(Foo::arr), std::end(Foo::arr), [](char const *str) { std::cout << str << std::endl; } );
}