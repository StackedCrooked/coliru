#include <iostream>
#include <memory>
#include <array>

class foo {
  std::size_t id;
  public:
  foo() : id(0) {}
  foo(std::size_t const _id) : id(_id) {}
  std::size_t getid() const { return id; }
};

auto main() ->int {
  
  std::array<std::unique_ptr<foo>, 3> arr;
  
  std::unique_ptr<foo> p1(new foo(1));
  arr[0] = std::move(p1);
  std::unique_ptr<foo> p2(new foo(2));
  arr[1] = std::move(p2);
  std::unique_ptr<foo> p3(new foo(3));
  arr[2] = std::move(p3);
  
  for(auto &i : arr) if(i != nullptr) std::cout << i->getid() << " ";
  std::cout << std::endl;
  
  // reset first position
  arr[0].reset();
  
  for(auto &i : arr) if(i != nullptr) std::cout << i->getid() << " ";
  std::cout << std::endl;
  
  return 0;
}