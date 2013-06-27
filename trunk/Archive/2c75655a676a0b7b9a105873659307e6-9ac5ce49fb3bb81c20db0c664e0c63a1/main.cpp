



#include <iostream>
#include <stdint.h>

unsigned char bleah;
int uhm;

template<const unsigned char& T> void foo()
{
  std::cout << "b" << std::endl;
}

template<int& T> void foo()
{
  std::cout << "a" << std::endl;
}


int main()
{
  foo<bleah> ();
  foo<uhm>();
  return(0);
}