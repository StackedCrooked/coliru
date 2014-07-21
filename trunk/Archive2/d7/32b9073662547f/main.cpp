#include <iostream>
#include <string>
#include <regex>

int main() {
  std::string str("[275, 61],[279, 56],[285, 54],[292, 55],[298, 57],[315, 57],[321, 54],[328, 54],[335, 56]");
  std::regex e ("\\[\\s*\\d+\\s*\\,\\s*\\d+\\s*\\]");
  std::smatch sm;
  std::regex_search(str, sm, e);
  std::cout << "the matches were: ";
  while (std::regex_search(str, sm, e)) {
    for (auto x : sm) std::cout << x << " ";
    std::cout << std::endl;
    str = sm.suffix().str();
  }
}