// swapping stringstream objects
#include <string>       // std::string
#include <iostream>     // std::cout
#include <sstream>      // std::stringstream

int main () {

  std::stringstream foo;
  std::stringstream bar;

  foo << 100;
  bar << 200;

  foo.swap(bar);

  int val;

  foo >> val; std::cout << "foo: " << val << '\n';
  bar >> val; std::cout << "bar: " << val << '\n';

  return 0;
}