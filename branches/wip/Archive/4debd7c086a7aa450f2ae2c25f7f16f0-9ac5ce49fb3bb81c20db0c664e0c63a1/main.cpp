#include <iostream>
#include <stdint.h>

const uint8_t myChar =42;
const int myInt = 42;

template<int T> void foo()
{
  std::cout << "a" << std::endl;
}

template<uint8_t T> void foo()
{
  std::cout << "b" << std::endl;
}

int main()
{
  foo<myChar> ();
  foo<myInt>();
  return(0);
}