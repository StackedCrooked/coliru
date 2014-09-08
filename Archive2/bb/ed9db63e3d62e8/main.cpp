#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

int main() {
  std::vector<std::string> letters {"ABC", "A", "BCDE", ""};
  std::for_each(letters.begin(), letters.end(), [](std::string &str) { if(!str.empty()) std::reverse(str.begin() + 1, str.end()); });
  for(auto i : letters) std::cout << i << std::endl;
}