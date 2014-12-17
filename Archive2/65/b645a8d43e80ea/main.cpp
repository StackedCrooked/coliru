#include <iostream>
#include <string>
#include <vector>

enum class Bob : uint32_t
{
  eBitA = 0x000F,   
};

void set(uint32_t& bob,
         bool state)
{
  bob = (bob & ~(uint32_t)Bob::eBitA) |
        (state ? (uint32_t)Bob::eBitA : (uint32_t)0);
}

int main()
{
  uint32_t bob = 0xF0;
  
  std::cout << "F = " << bob << std::endl;
  set(bob, true);
  std::cout << "T = " << bob << std::endl;
  set(bob, false);
  std::cout << "F = " << bob << std::endl;
  set(bob, true);
  std::cout << "T = " << bob << std::endl;
  set(bob, true);
  std::cout << "T = " << bob << std::endl;
  set(bob, false);
  std::cout << "F = " << bob << std::endl;
  set(bob, false);
  std::cout << "F = " << bob << std::endl;
  
  
  return 0;
}
