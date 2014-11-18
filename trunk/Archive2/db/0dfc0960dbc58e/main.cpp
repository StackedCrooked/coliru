#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    //                     o  o  o  o  e  e  e  e
    std::vector <int> v1 { 1, 3, 5, 7, 2, 4, 6, 8 };
    //                     o  o  o  o  e  O  e  e  
    std::vector <int> v2 { 1, 3, 5, 7, 2, 3, 6, 8 };
    
    // Zwróci 1.
    std::cerr << std::is_partitioned (v1.cbegin (), v1.cend (), std::bind (std::modulus <int> (), std::placeholders::_1, 2)) << std::endl;
    // Zwróci 0, bo ostatnia trójka psuje szyk.
    std::cerr << std::is_partitioned (v2.cbegin (), v2.cend (), std::bind (std::modulus <int> (), std::placeholders::_1, 2)) << std::endl;
}
