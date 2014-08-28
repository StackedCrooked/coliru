#include <algorithm> 
#include <iostream>
#include <vector> 

int main() 
{ 
    std::vector<int> v{30, 10, 40, 10, 50, 90}; 
    int x = 44;
    std::transform(v.begin(), v.end(), v.begin(), [x](int v){return v-x;});
    std::vector<int>::iterator result = std::min_element(std::begin(v), std::end(v), [](int a, int b) { return std::abs(a) < std::abs(b); } ); 
    std::cout << "closest element: " << *result+x << " (at: " << std::distance(std::begin(v), result) << ")" << std::endl; 
} 