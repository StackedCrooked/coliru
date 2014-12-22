#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
     const std::vector<int> seq = { 2, 16, 8, 56, 64, 66, 20, 12, 18 } ;
     std::cout << std::boolalpha ;

     const auto is_even = [] ( int i ) { return i%2 == 0 ; };
     std::cout << "all even numbers? " << std::all_of( seq.begin(), seq.end(), is_even ) << '\n' ;

     const auto is_divisible_by_7 = [] ( int i ) { return i%7 == 0 ; };
     std::cout << "at least one divisible by 7? " << std::any_of( seq.begin(), seq.end(), is_divisible_by_7 ) << '\n' ;

     const auto greater_than_100 = [] ( int i ) { return i > 100 ; };
     std::cout << "none greater than 100? " << std::none_of( seq.begin(), seq.end(), greater_than_100 ) << '\n' ;
}
