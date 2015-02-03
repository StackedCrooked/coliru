#include <string>
#include <iostream>
int main() {
  using namespace std::string_literals;
  std::cout << "some string"s + "another string"s; 
}