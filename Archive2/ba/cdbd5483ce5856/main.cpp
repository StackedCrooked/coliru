#include <iostream>
#include <string>
#include <algorithm>

int main() {
  std::string sym("$]};:,%<.>/?");
  std::string let("opqrstuvwxyz");

  std::string inpt;
  while (std::getline(std::cin, inpt)) {
    for (std::size_t i(0), ie(inpt.size()); i < ie; ++i) {
      std::size_t idx = std::distance(sym.begin(), std::find(sym.begin(), sym.end(), inpt[i]));
      if (idx < sym.size()) std::cout << let[idx];
    }
    std::cout << std::endl;
  }

  return 0;
}