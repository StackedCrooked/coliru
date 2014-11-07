#include <iostream>
#include <functional>
#include <map>

class A {
public:
  static void f(const std::string &s, int c) { std::cout << s; }
}; 

std::map<std::string, std::function<void(std::string const &, int)>> fs; 

int main() {
  fs["f"] = &A::f;
  fs["f"]("hello", 3);
  A::f("", 3);
}