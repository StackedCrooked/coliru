#include <iostream>
#include <list>
#include <iterator>

int main()
{
    std::list<int> seq { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 } ;
    std::size_t M = 27 ;

    // locate the M-th element (M==0 is the first) in the sequence
    // the sequence is treated as a circular list
    // move forward M%N places where N is the number of elements in the sequence
    if( !seq.empty() )
    {
        auto iter = std::begin(seq) ;
        std::advance( iter, M % seq.size() ) ; // move forward places
        // http://en.cppreference.com/w/cpp/iterator/advance

        std::cout << "the " << M << "th element is: " << *iter << '\n' ;
    }
}
