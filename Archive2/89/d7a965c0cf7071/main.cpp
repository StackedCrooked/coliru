#include <iostream>
#include <sstream>
#include <vector>
#include <string>

int main() {
  std::string str;
  std::getline(std::cin, str);
  std::stringstream sstrm(str);
  std::vector<int> v;
  int i;
  while (sstrm >> i) {
    v.push_back(i);
  }
  if (!sstrm.fail()) {
    for (auto i : v) std::cout << i << " ";
    std::cout << std::endl;
  } else {
    std::cout << "Reading failed!" << std::endl;
  }

  return 0;
}