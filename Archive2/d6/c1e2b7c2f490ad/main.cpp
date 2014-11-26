#include <string>       // std::string
#include <iostream>     // std::cout
#include <sstream>      // std::stringstream

int main () {

  std::stringstream stream("1234");

  std::stringstream stream2 = std::move(std::stringstream("5678"));

  return 0;
}