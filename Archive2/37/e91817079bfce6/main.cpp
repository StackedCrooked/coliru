#include <boost/range/adaptor/sliced.hpp>
#include <boost/range/algorithm/copy.hpp>
#include <boost/range/adaptor/reversed.hpp>
#include <iterator>
#include <iostream>
#include <vector>

int main(int argc, const char* argv[])
{
  using namespace boost::adaptors;

  std::vector<int> x { 2, 3, 5, 7, 11, 13, 17, 19 }; 
  for (auto i : x | boost::adaptors::sliced(2, 5)) 
    std::cout << i << ' ';
    
  for (auto i : x | boost::adaptors::sliced(2, 5) | boost::adaptors::reversed ) 
    std::cout << i << ' ';

    return 0;
}