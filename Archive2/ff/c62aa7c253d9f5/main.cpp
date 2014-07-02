#include <cstring>
#include <fstream>
#include <iostream>

struct stEjemplo
{
    char cadena1[9];
    char cadena2[9];
};

std::ostream& operator<<(std::ostream& os, const stEjemplo& e)
{
  return os << e.cadena1 << ' ' << e.cadena2;
}

int main()
{
  stEjemplo somest = {};
  std::strcpy(somest.cadena1, "SomeText");
  std::strcpy(somest.cadena2, "SomeText");
  std::ofstream file("File.dat", std::ios::trunc);
  if(!file)
  {
    std::cout << "Failed opening file.\n";
  }
  file << somest;
  file.close();
  
  // no error checking, assuming all will go well
  std::ifstream test("File.dat");
  std::string contents;
  std::getline(test, contents);
  std::cout << contents;
}