#include <boost/flyweight.hpp>
#include <iostream>
#include <string>
#include <boost/version.hpp>

int main()
{
  boost::flyweight<std::string> f{"hello"};
  std::cout<<f<<std::endl;
  
  std::cout<<BOOST_LIB_VERSION<<std::endl;
}
