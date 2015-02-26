#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

// how it can copy in the "receive" end
void fillVector(std::vector<int>& v1) {
    // c++11 initializer list syntax:
    int arr[] = {1,2,3,4,5,6};
    int size = 6;
    v1.resize(size);
    std::copy(std::begin(arr), std::begin(arr) + size, std::begin(v1));    
}

int main() 
{
    std::vector<int> v1;
    fillVector(v1);
    
    for (auto i: v1) {
        std::cout << i << std::endl;
    }
}