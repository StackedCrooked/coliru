
#include <algorithm>
#include <iostream>

int main () {
    int transitTime [10] = {1,2,3,4,5,6,7,8,9,10};
    
    auto minAndMax = std::minmax_element(std::begin(transitTime),std::end(transitTime));
    std::cout << "Smallest: " << *minAndMax.first 
        << "\nLargest: " << *minAndMax.second;
}