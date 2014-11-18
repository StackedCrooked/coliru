#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    std::vector <int> v1 { 1, 2, 3, 4, 5,  6, 7, 8,  9 }; 
    std::vector <int> v2 { 1, 2, 3, 4, 88, 6, 7, 66, 9  }; 

    std::pair <std::vector <int>::const_iterator, std::vector <int>::const_iterator> p =
        std::mismatch (v1.cbegin (), v1.cend (), v2.cbegin ());

    std::cerr << *p.first << ", " << *p.second << std::endl;
}
