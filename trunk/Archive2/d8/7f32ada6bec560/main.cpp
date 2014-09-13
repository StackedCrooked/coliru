#include <iostream>
#include <string>
#include <algorithm>

struct Foo {
    static std::string const arr[];
};

std::string const Foo::arr[] = {"ace_hearts", "2_hearts", "3_hearts"};

int main() {
  std::for_each(std::begin(Foo::arr), std::end(Foo::arr), [](std::string const &str) { std::cout << str << std::endl; } );
}