#include <iostream>
#include <bitset>

long long F(long long const k) {
  return std::abs(static_cast<int>(std::bitset<64>(k & 0x5555555555555555).count()) - 
                  static_cast<int>(std::bitset<64>(k & 0xaaaaaaaaaaaaaaaa).count()));
}

int main() {
  std::cout << F(3) << std::endl;
  std::cout << F(4) << std::endl;
  std::cout << F(5) << std::endl;
  std::cout << F(12345678) << std::endl;
}