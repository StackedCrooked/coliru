 #include <iostream>

int main() {
  int a = 0x5555;
  int b = 0xFFFF;
  std::cout  << std::hex << ( a ^ b ) << std::endl;
}