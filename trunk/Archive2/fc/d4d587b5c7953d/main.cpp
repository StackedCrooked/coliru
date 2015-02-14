#include <iostream>
#include <functional>
#include <memory>
#include <cassert>

std::unique_ptr<int> make_int(int value) {
  return std::unique_ptr<int>(new int(value));
}

std::unique_ptr<int> add(std::unique_ptr<int> a, std::unique_ptr<int> b) {
  assert(a);
  assert(b);
  return make_int(*a + *b);
}

int main()
{
  auto f5 = std::bind([](std::unique_ptr<int> & a, std::unique_ptr<int> & b) {
    return add(std::move(a), std::move(b));
  }, make_int(1), make_int(2));

  std::cout << *f5() << std::endl;
  std::cout << *f5() << std::endl;
}
