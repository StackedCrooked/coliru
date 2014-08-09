#include <iostream>
#include <string>
#include <vector>

int main() {
  std::vector<std::string> v(10, "apples");  
  for(auto &&word : v) {
    word[0] = toupper(word[0]);
    std::cout << word << std::endl;
  }
}