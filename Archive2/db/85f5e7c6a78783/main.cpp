#include <iostream>
#include <string>
#include <initializer_list>

class A
{
 public:
  A(int, bool) { std::cout << __PRETTY_FUNCTION__ << std::endl; }
  A(int, double) { std::cout << __PRETTY_FUNCTION__ << std::endl; }
  
  template <typename T, typename=std::enable_if_t<std::is_same<int, T>{}>>
  A(std::initializer_list<T>) { std::cout << __PRETTY_FUNCTION__ << std::endl; }
};

int main()
{
    A a1 = {1, 1.0};
    A a2 = {1, 1};
}