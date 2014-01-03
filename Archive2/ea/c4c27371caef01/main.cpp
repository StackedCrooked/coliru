#include <iostream>
#include <iomanip>
#include <algorithm>
#include <array>
#include <boost/iterator/permutation_iterator.hpp>

int main()
{
    int a[5][5] = {{2,  5,  7, 4, 8}, 
                   {3, 11, 14, 5, 2}, 
                   {6,  3, 12, 9, 1},
                   {7, 15, 11, 4, 2},
                   {8, 16, 13, 5, 1}}; 

    // indexes into the original array
    // (for full credit, write the function that builds these)
    std::array<std::size_t, 25> idx = {0,
                                       1,5,
                                       2,6,10,
                                       3,7,11,15,
                                       4,8,12,16,20,
                                         9,13,17,21,
                                           14,18,22,
                                              19,23,
                                                 24};

    std::sort(boost::make_permutation_iterator(&a[0][0], idx.begin()),
              boost::make_permutation_iterator(&a[0][0], idx.end()));

    for(auto& row: a) {
        for(int el: row)
            std::cout << std::setw(2) << el << ' ';
        std::cout << '\n';
    }
}
