#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    std::vector <int> v1 { 1, 2, 3, 4, 6, 8 };    
    std::vector <int> v2 { 3, 4, 5, 6, 8, 10 };    
    std::vector <int> v3 { 1, 2, 3, 4, 99, 8 };    

    // Sprawdza parzystość obydwu liczb.
    auto op = [] (int a, int b) {
        return a%2 == b%2;
    };

    std::cerr << std::equal (v1.cbegin (), v1.cend (), v2.cbegin (), op) << std::endl;
    std::cerr << std::equal (v1.cbegin (), v1.cend (), v3.cbegin (), op) << std::endl;
}
