#include <iostream>
#include <set>

int main()
{
  std::set<int> one = {1, 2, 3, 4, 5};
  std::set<int> two = {2, 4, 6, 8, 10};
  
  one.insert(std::begin(two), std::end(two));
  
  for(int i : one)
    std::cout << i << '\n';
}