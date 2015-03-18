#include <iostream>
#include <string>
#include <initializer_list>
#include <vector>


class Foo {
    std::vector<int> bar;
  public:
    Foo(std::initializer_list<int> i) : bar(i) { }
};  


int main() {
  Foo foo{1, 2, 3};
}
