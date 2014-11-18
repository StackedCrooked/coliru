#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

int main()
{
    std::vector <int> v1 { 100, 19, 36, 17, 3, 25, 1, 2, 7 };
    std::cerr << std::is_heap (v1.cbegin (), v1.cend ()) << std::endl;

//std::vector <int> v1 { 88,80,86,71,75,44,49,50,64,44,31,35,43,7,40,50,43,4,59,5 };
//    std::cerr << std::is_heap (v1.cbegin (), v1.cend ()) << std::endl;
    
    
    // std::make_heap (v1.begin (), v1.end ());
    // std::copy (v1.cbegin (), v1.cend (), std::ostream_iterator <int> (std::cout, ","));

}
