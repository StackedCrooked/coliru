#include <iostream>
#include <string>
#include <vector>

int print_all(std::vector<std::string> words) {
  for (auto word : words)
    std::cout << word << " ";
  std::cout << std::endl;
}

int main() {
  std::vector<std::string> words{ "Hello", "from", "gcc", __VERSION__ };
  print_all(words);
  return 0;
}