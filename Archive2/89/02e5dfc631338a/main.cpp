#include <iostream>
#include <utility>
#include <string>

struct A {
  std::string _data;

  template<class T>
  void set (T&& data)
    noexcept (noexcept (_data = std::forward<T> (data)))
  {
    _data = std::forward<T> (data);
  }
};

int main () {
  auto x = A {}; 
  auto s = std::string { "hello world" };

  std::cout << noexcept (x.set (std::move (s)))    << std::endl;
  std::cout << noexcept (x.set (s))                << std::endl;
  std::cout << noexcept (x.set ("c-style string")) << std::endl;
}