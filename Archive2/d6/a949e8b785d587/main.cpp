#include <iostream>
#include <string>
#include <functional>

int main(int argc, char **argv) {
  std::string test = "fdsa";

  auto fn = std::bind(static_cast<std::string&(std::string::*)(const std::string&)>(&std::string::append), &test, std::string("test"));
  fn();
  std::cout << test << '\n';
}