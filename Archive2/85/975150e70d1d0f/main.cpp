#include <iostream>
#include <string>

int main()
{
  const std::string test("root75/obj_43.dat");
  int number;
  // validate input:
  const auto index = test.find("obj_");
  if(index != std::string::npos)
  {
    number = std::stoi(test.substr(index+4));
    std::cout << "number: " << number << ".\n";
  }
  else
    std::cout << "Input validation failed.\n";
}