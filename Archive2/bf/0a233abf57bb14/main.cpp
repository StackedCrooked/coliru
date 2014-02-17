#include <cstdlib>
#include <iostream>

int main()
try
{
  throw 42;
}
catch(int i)
{
  std::cout << "Caught int: " << i << ". Exiting...\n";
  std::exit(EXIT_FAILURE);
}
