#include <vector>
#include <set>
#include <iostream>
#include <algorithm>
#include <iterator>
 
int main()
{
    std::vector<int> v1 = {1, 2, 3, 4, 5}; 
    std::vector<int> v2 = {      3, 4, 5, 6, 7}; 
    std::vector<int> dest1;
 
    std::set_union(v1.begin(), v1.end(),
                   v2.begin(), v2.end(),                  
                   std::back_inserter(dest1));
 
    for (const auto &i : dest1) {
        std::cout << i << ' ';
    }   
    std::cout << '\n';
}