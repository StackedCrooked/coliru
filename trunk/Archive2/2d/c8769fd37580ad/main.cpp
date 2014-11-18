#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    std::vector <int> v1 { 1, 2, 3, 4, 6, 8 };    
    std::vector <int> v2 { 1, 2, 3, 4, 6, 8 };    
    std::vector <int> v3 { 1, 2, 3, 4, 99, 8 };    

    std::cerr << std::equal (v1.cbegin (), v1.cend (), v2.cbegin ()) << std::endl;
    std::cerr << std::equal (v1.cbegin (), v1.cend (), v3.cbegin ()) << std::endl;
}
