#include <iostream>
#include <vector>
#include <boost/range/adaptor/filtered.hpp>
#include <boost/range/algorithm/copy.hpp>

using boost::adaptors::filtered;
int main()
{
  std::vector<int> numbers = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
  auto is_odd = [](int x){ return x % 2 == 1; };
  copy(numbers | filtered(is_odd), std::ostream_iterator<int>(std::cout, "\n"));
}