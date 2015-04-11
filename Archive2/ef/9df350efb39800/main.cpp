#include <iostream>
#include <string>
#include <vector>

void func (int&) { std::cerr << __PRETTY_FUNCTION__ << std::endl; }
void func (long) { std::cerr << __PRETTY_FUNCTION__ << std::endl; }

template<class T>
void func (std::vector<T> vec)
{
  std::cout << __PRETTY_FUNCTION__ << "{ ";
  for (auto const& e : vec) { std::cout << e << " "; }
  std::cout << "}";
}

int main () {
  int foo = 123;

  auto p1 = static_cast<void(*)(int&)>(&func);
  auto p2 = static_cast<void(*)(long)>(&func);
  auto p3 = static_cast<void(*)(std::vector<int>)>(&func);

  p1 (foo);
  p2 (3.14f);
  p3 ({1,2,3});
}