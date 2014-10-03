#include <vector>
#include <iostream>
#include <algorithm>

int main()
{
    // move 5 from 4th to 1st index
    
    std::vector<int> v {1,2,3,4,5,6};
    // position:        0 1 2 3 4 5
    
    std::size_t i_old = 4;
    std::size_t i_new = 1;
    auto it = v.begin();
    
    std::rotate( it + i_new, it + i_old, it + i_old + 1);
    for (int i : v) std::cout << i << ' ';
}