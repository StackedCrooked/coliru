#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    //                   0                 6
    std::vector <int> v {1, 3, 4, 5, 6, 8, 9, 9, 10, 11, 12 };    
    // Znajdź pierwszą parę takich samych liczb.
    auto it = std::adjacent_find (v.cbegin (), v.cend ());
    std::cerr << std::distance (v.cbegin (), it) << std::endl;
}
