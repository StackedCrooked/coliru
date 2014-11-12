#include <algorithm>
#include <iostream>
#include <tuple>
#include <vector>

using index = uint32_t;
using value = float;
using sparse_entry = std::tuple<index, index, value>;
using sparse_matrix = std::vector<sparse_entry>;

int main()
{
    // sparse 3x3 matrix
    auto m = sparse_matrix { 
        std::make_tuple( 1, 1, -2.2), 
        std::make_tuple( 1, 0, 42  ), 
        std::make_tuple( 0, 2,  3.4), 
        std::make_tuple( 0, 1,  1.7) 
    };    
    
    std::sort(begin(m), end(m), [](auto const& L, auto const& R) {
        return 
            std::forward_as_tuple(std::get<0>(L), std::get<1>(L)) <
            std::forward_as_tuple(std::get<0>(R), std::get<1>(R))
        ;
    });
    
    for (auto const& elem : m)
        std::cout << "{ " << std::get<0>(elem) << ", " << std::get<1>(elem) << ", " << std::get<2>(elem) << "}, \n";
}
