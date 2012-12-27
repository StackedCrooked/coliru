#include <boost/config.hpp>
#include <boost/version.hpp>
#include <iostream>

int main()
{
  std::cout << "Boost: " << BOOST_LIB_VERSION << std::endl;
  std::cout << "Compiler: " << BOOST_COMPILER << std::endl;
  std::cout << "Stdandard Library: " << BOOST_STDLIB << std::endl;
  return 0;
}

