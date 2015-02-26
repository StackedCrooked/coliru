#include <iostream>     // std::cin, std::cout
#include <fstream>      // std::ifstream

int main () {
  char str[256];

  std::cout << "Enter the name of an existing text file: ";
  std::cin.get (str,256);    // get c-string

  std::ifstream is(str);     // open file

  while (is.good())          // loop while extraction from file is possible
  {
    char c = is.get();       // get character from file
    if (is.good())
      std::cout << c;
  }

  is.close();                // close file

  return 0;
}