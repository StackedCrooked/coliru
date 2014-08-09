#include <iostream>
#include <string>
#include <vector>

int main() {
  std::vector<std::string> v(10, "apples");  
  for(auto it(v.begin()), ite(v.end()); it != ite; ++it) {
    *(it->begin()) = toupper(*(it->begin()));
    std::cout << *it << std::endl;
  }
}