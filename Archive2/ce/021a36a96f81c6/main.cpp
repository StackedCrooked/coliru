#include <iostream>
#include <string>
#include <boost/multi_array.hpp>

int main() {
    boost::multi_array<std::string, 2> a(boost::extents[3][5]);
    for(size_t x = 0; x < a.shape()[0]; x++) {
        for(size_t y = 0; y < a.shape()[1]; y++) {
            std::ostringstream sstr;
            sstr << "[" << x << ", " << y << "]";
            a[x][y] = sstr.str();
        }
    }
    for(size_t x = 0; x < a.shape()[0]; x++) {
        for(size_t y = 0; y < a.shape()[1]; y++) {
            std::cout << a[x][y] << "\n";
        }
    }
    return 0;
}