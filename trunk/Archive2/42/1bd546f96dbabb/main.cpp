#include <boost/range/adaptor/strided.hpp>
#include <boost/range/adaptor/reversed.hpp>
#include <boost/assign.hpp>
#include <iterator>
#include <iostream>
#include <vector>

int main()
{
  std::vector<int> input = {1,2,3,4,5,6,7,8,9,10};

  for(const auto& element : boost::adaptors::reverse(input))
    std::cout << element << '\n';
  std::cout << '\n';

  for(const auto& element : boost::adaptors::stride(input,2))
    std::cout << element << '\n';
}
