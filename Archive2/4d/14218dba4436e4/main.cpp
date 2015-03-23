#include <iostream>
#include <string>

inline std::string
operator""_s(const char* __str, size_t __len)
{ return std::string{__str, __len}; }
    
std::string operator+ (std::string stuff, int why) {
  return stuff + std::to_string(why);
}
    
void print(std::string str) {
  std::cout << str << std::endl;
}

int main() {
  print("die"_s + 1);
  return 0;
}