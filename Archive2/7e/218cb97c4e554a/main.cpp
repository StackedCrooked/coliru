#include <iostream>
#include <string>

int main() {
  int i = 1232323223;
  std::string str = std::to_string(i);
  std::cout << "Number of Digits: " << str.size() <<std::endl;
}