#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    std::vector <int> v {-1, 1, -1, 2, -3, 4, -5, 5, -5};    
    // Najmniejsza wartość bezwzględna (1, czyli na pozycji 0)
    std::cerr  << std::distance (v.begin (), std::min_element (
            v.begin (), 
            v.end (), 
            [] (int a, int b) { return std::abs (a) < std::abs (b); })) << std::endl;
    
}
