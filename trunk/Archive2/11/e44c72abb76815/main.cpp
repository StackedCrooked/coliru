#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <stdint.h>

int32_t someFunctionIWantToTest(){ 
  return 1;
}

int main()
{
std::cout << someFunctionIWantToTest() << std::endl;  
}
