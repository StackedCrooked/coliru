#include <iostream>
#include <memory>
#include <functional>

int main()
{
  bool should_delete{};
  std::unique_ptr<int, std::function<void (int*)>> ptr(nullptr, [&](int * const i)
  {
    if(should_delete)
    { std::cout << "deleting" << std::endl; }
  });

  bool input{};
  ptr.reset(new int{});
  if((std::cin >> input) && input)
  { should_delete = true; }
}