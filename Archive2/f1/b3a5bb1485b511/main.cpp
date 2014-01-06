#include <iostream>
#include <string>

int main(int argc, char** argv)
{
  std::cout.precision(17);
  std::cout << double(0.8f) << std::endl;
  std::cout << double(0.3f) << std::endl;
  std::cout << double(1.8f) << std::endl;
  std::cout << double(0.85f) << std::endl;
  std::cout << double(1.2f) << std::endl;
  return 0;
}
