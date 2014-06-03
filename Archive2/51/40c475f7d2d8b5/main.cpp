#include <sstream>
#include <iostream>

int main(int argc, const char **args)
{
  double val(0);
  std::stringstream ss("2i");
  ss >> val;
  std::cout << "val=" << val << "; fail=" << ss.fail() << std::endl;
  return 0;
}