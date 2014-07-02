#include <iostream>
#include <string>
#include <unordered_set>
#include <algorithm>

int main() {
  std::string str("Hello World!");
  std::unordered_set<char> log;
  std::cout << "Before: " << str << std::endl;
  str.erase(std::remove_if(str.begin(), str.end(), [&] (char const c) { return !(log.insert(c).second); }), str.end());
  std::cout << "After:  " << str << std::endl;
}