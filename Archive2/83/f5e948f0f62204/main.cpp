#include <iostream>
#include <memory>



int main()
{
  std::unique_ptr<int> p = std::make_unique<int>(3); 
  auto f = [=](int j){ for(int i(0); i < j; i++) printf("blah"); }; 
  f(2); 
}
