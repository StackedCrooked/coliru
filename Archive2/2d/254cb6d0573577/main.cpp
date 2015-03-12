#include <iostream>
#include <algorithm>
#include <vector>
 
int main() 
{
    std::vector<int> v{1,2,3,1,2,3,3,4,5,4,5,6,7};
    std::sort(v.begin(), v.end()); 
    auto last = std::unique(v.begin(), v.end());
    v.erase(last, v.end());
    for (const auto& i : v)
      std::cout << i << " ";
    std::cout << "\n";
}