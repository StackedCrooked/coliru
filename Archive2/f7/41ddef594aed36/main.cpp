#include <iostream>
#include <vector>
#include <algorithm>

int main() {

    std::vector<int> x = {15, 3, 0, 20};
    
    std::vector<int> y;
    
    std::size_t i = 0;
    std::transform( std::begin(x),
                    std::end(x), 
                    std::back_inserter(y),
                    [&](int v) { return i++; } );
    
    std::sort(  std::begin(y), 
                std::end(y),
                [&](int i1, int i2) { return x[i1] < x[i2]; } );
    
    // Put the sorted indices of x into the vector y
    for (auto v : y)
        std::cout << v << " ";

    return 0;
}