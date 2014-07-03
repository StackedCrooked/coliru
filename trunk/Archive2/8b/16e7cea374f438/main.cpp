#include <string>
#include <iostream>

void test(const std::string&) { std::cout << "test!" << std::endl; }

int main() {
  test({'a'});
}