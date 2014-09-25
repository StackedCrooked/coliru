#include <iostream>
#include <string>

int main()
{
  const std::string test("obj_42");
  int number;
  // validate input:
  if(test.length() == 6 && test[0] == 'o' && test[1] == 'b' && test[2] == 'j' && test[3] == '_')
  {
    number = std::stoi(test.substr(4));
    std::cout << "number: " << number << ".\n";
  }
  else
    std::cout << "Input validation failed.\n";
}