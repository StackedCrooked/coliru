#include <iostream>
#include <cstdint>

template<typename T> void foo()
 {}
 
template<> void foo<int>()
{
  std::cout << "a" << std::endl;
}

template<> void foo<uint8_t>()
{
  std::cout << "b" << std::endl;
}

int main()
{
  foo<uint8_t> ();
  foo<int>();
  return(0);
}