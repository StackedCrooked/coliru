#include <boost/multi_array.hpp>
#include <iostream>
#include <fstream>

using array_type = boost::multi_array<int, 2>;
using index = array_type::index;

array_type fill() {
    int w, h;
    std::cin >> w >> h;
    array_type arr(boost::extents[w][h]);
    for (index i = 0; i < w; ++i)
        for (index j = 0; j < h; ++j)
            std::cin >> arr[i][j];
    return arr;
}

int main() {
    std::cin.exceptions(std::ifstream::failbit);
    auto arr = fill();
    for (auto row : arr) {
        std::cout << "{ ";
        for (auto el : row)
            std::cout << el << " ";
        std::cout << "}\n";
    }
}