#include <iostream>
#include <string>
#include <vector>

int main()
{
    std::string name;
  std::cout << "What is your name? \n";
  getline (std::cin, name);
  std::cout << "Hello, " << name << "!\n";
}
