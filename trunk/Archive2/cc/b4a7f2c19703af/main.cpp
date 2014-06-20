#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>

auto main() -> int
{
  std::set<int > a{ 1, 2, 3, 4, 5};
  std::vector<std::unordered_set<int>> b(1);
  b[0].insert(a.begin(), a.end()); 
  
  for(auto i : b) {
    for(auto j : i) {
      std::cout << j << " ";    
    }    
    std::cout << std::endl;
  }
  return 0;
}