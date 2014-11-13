#include <iostream>
#include <iterator>
#include <vector>
#include <algorithm>

int main()
{
    std::vector <int> v {1, 2, 3, 4};

    std::for_each (v.begin (), v.end (),
        std::for_each (v.begin (), v.end (), [] (int &i) { ++i; }));
        
    // Uwaga : ostream_iterator używamy z copy, a nie z for_each, includujemy
    // <iterator>, a ostatni parametr typu char *, a nie char.
    std::copy (v.cbegin (), v.cend (), std::ostream_iterator <int> (std::cerr, ","));
}
