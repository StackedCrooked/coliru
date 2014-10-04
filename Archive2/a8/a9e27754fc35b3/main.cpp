#include <vector>
#include <cassert>
#include <iostream>
#include <algorithm>
int main()
{
  std::vector<std::pair<int, int>> v = {{1,2}, {3,4}, {5,6}};
  auto p = std::make_pair(3, 4);

  assert(std::is_sorted(v.begin(), v.end())); // can binary search

  if(std::binary_search(v.begin(), v.end(), p))
      std::cout << "yes\n";
}
