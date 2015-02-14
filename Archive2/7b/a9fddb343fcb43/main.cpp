#include <iostream>
#include <memory>

int main()
{
  auto p = std::unique_ptr<int>(new int(1));

  std::cout << *std::move(p) << std::endl;
  std::cout << *std::move(p) << std::endl;
}
