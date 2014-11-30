#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator> // for std::back_inserter

int main ()
{
    std::vector<int> info1 = { 1, 1, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 5, 6, 7, 8, 9, 45, 66, 455 } ;
    std::vector<int> info2 = { 1, 2, 2, 3, 3, 4, 5, 5, 6, 8, 8, 9, 16, 24, 45, 45, 49, 66, 88, 455 } ;

    std::vector<int> info3 ; // empty vector

    // std::back_insert_iterator adds elements to the end of info3
    // http://en.cppreference.com/w/cpp/iterator/back_inserter
    std::set_union( info1.begin(), info1.end(),
                    info2.begin(), info2.end(),
                    std::back_inserter(info3) ) ; // ********
    
    if( !info3.empty() )
    {
        for( std::size_t i=0; i<info3.size()-1; i++ ) // Printing out list til second to last
            std::cout << info3[i] << ", "; // Output
            
        std::cout << info3.back() << ".\n" ; // Prints last item for proper format
    }
}
