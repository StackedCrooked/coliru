#include <iostream>
#include <iomanip>

int main() {
  std::cout << std::hex << 'ø';
  std::cout << std::hex << '\u00F8';
  std::cout << std::hex << '\xc3\xb8';
}
