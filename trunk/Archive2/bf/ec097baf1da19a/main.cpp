#include <iostream>
#include <memory>
#include <typeinfo>

int main()
{
  std::unique_ptr<int*> ptrptr;
  std::cout << typeid(&*ptrptr).name() << std::endl;
}