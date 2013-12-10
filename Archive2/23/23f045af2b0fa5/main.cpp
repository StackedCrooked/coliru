#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>

int main(int, char*[]) {
    std::vector<int> x { 0, 2, 4 };
    std::vector<int> y { 1, 3, 5 };
    std::vector<int> z;

    std::merge(
        std::begin(x), std::end(x), 
        std::begin(y), std::end(y), 
        std::back_inserter(z)
    );
    
    std::copy(std::begin(z), std::end(z), std::ostream_iterator<int>(std::cout));
}