#include <iostream>
#include <memory>

int main()
{
  std::unique_ptr<int> p(new int(3)); 
  auto f = [=](int j){ *p = j; }; 
  f(2); 
}