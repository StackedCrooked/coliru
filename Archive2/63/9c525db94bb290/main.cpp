
#include <iostream>

int main ()
{
  std::cout << noexcept(std::move(1)) << std::endl;
}