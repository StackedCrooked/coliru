#include <iostream>

int main() {
  std::string a = "abcde";
  std::string b;
  std::cin.getline(b);
  std::cout << a << ' ' << b;
  return 0;
}