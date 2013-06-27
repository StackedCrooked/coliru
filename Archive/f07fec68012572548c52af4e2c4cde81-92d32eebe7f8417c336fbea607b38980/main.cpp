#include <iostream>
#include <cstdint>

template<typename T> void foo(T in)
 {}
 
template<> void foo(int in)
{
  std::cout << "a" << std::endl;
}

template<> void foo(uint8_t in)
{
  std::cout << "b" << std::endl;
}

int main()
{
  foo(static_cast<uint8_t>(42));
  foo(static_cast<int>(42));
  return(0);
}