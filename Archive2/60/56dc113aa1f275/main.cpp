#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    std::vector <int> v1 {1, 2, 3, 4, 5, 3, 6, 7, 8, 9 };
    std::vector <int> v2 {7, 7};
    
    // Porównuje parzystość elementów. Zatem szukamy ciągu 2 nieparzystych 
    // elementów w v1 (jest to 5 i 3 na 4 pozycji):
    auto it = std::search (v1.cbegin (), v1.cend (), v2.cbegin (), v2.cend (), [] (int a, int b) { 
        return a % 2 == b % 2; });
        
    std::cerr << std::distance (v1.cbegin (), it) << std::endl;
}
