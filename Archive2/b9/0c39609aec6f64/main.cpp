#include <iostream>
#include <vector>

auto main() -> int
{
  std::vector<int> a{ 1, 2, 3, 4, 5};
  std::vector<std::vector<int>> b;
  b.emplace_back({a.begin(), a.end()}); 
  
  for(auto i : b) {
    for(auto j : i) {
      std::cout << j << " ";    
    }    
    std::cout << std::endl;
  }
  return 0;
}