#include <iostream>
#include <memory>

int main()
{
  std::unique_ptr<int> p = std::make_unique<int>(3); 
  auto f = [=](int j){ *p = j; }; 
  f(2); 
}