#include <iostream>
#include <boost/container/flat_set.hpp>

int main()
{
  boost::container::flat_set<int> one = {1, 2, 3, 4, 5};
  boost::container::flat_set<int> two = {2, 4, 6, 8, 10};
  
  one.insert(std::begin(two), std::end(two));
  
  for(int i : one)
    std::cout << i << '\n';
}