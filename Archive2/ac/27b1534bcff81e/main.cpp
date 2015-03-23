#include <iostream>
#include <string>

inline std::string
operator""_s(const char* str, size_t len)
{ return std::string{str, len}; }
    
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