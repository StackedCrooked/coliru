#include <iostream>
#include <boost/range/adaptor/reversed.hpp>


int main()
{
  //std::vector<int> omg = {3, 4, 5};
  int omg[] = {3, 4, 5};

  for ( auto && e : omg | boost::adaptors::reversed )
  {
    std::cout << e << std::endl;
  }
  return 0;
}