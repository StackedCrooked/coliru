#include <boost/flyweight.hpp>
#include <iostream>
#include <string>

int main()
{
  boost::flyweight<std::string> f={"hello"};
  std::cout<<f<<std::endl;
}
