#include <iostream>

#define UINT16 unsigned short  
UINT16 data[32];

int main() {
  std::cout << sizeof(UINT16) << std::endl;
  std::cout << sizeof(data)   << std::endl;
}