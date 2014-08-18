#include <iostream>
#include <string>
#include <bitset>
#include <random>
#include <climits>


template<typename T>
std::string to_binary_string(T const &val) {
  return std::string(std::bitset<sizeof(T) * CHAR_BIT>(val).template to_string<char,std::string::traits_type,std::string::allocator_type>());
}

int main() {
  std::random_device rd;
  std::mt19937 gen(rd());
  
  std::uniform_int_distribution<> dis(0, 20);
  int ival = dis(gen);
  
  std::cout << ival << " -> " << to_binary_string(ival) << std::endl;
}