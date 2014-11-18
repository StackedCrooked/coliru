#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    //                     o  o  o  o  e  e  e  e
    std::vector <int> v1 { 1, 3, 5, 7, 2, 4, 6, 8 };

    // Wypisze "2", bo 2 jest pierwszą liczbą z "drugiej części".
    std::cerr << *std::partition_point (v1.cbegin (), v1.cend (), std::bind (std::modulus <int> (), std::placeholders::_1, 2)) << std::endl;
}
