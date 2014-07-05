#include <utility>
#include <vector>
#include <iostream>
#include <string>

struct foo {
  std::string id;
  
  foo() : id("123456789")                    { std::cout << "Default Constructor Evoked!"            << std::endl; }
  foo(foo const &)                           { std::cout << "Copy Constructor Evoked!"               << std::endl; }
  foo(foo &&other) : id(std::move(other.id)) { std::cout << "Move Constructor Evoked!"               << std::endl; }
  ~foo()                                     { std::cout << "Destructor for ID(" << id << ") Evoke!" << std::endl; }
};

int main() {
  std::vector<foo> v;
  {
    foo tmp;
    v.push_back(std::move(tmp));
  }
}