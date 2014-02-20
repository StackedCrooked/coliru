#include <string>
#include <algorithm>
#include <iterator>
#include <iostream>

int main()
{
    std::string array[] { "utah", "utah", "utah", "virginia", "maryland", "maryland", "maryland", "virginia" } ;
    
    // remove the consecutive duplicates but retain the order of the strings in the array. 
    // If duplicates are non-consecutive they do not count. 
    // http://en.cppreference.com/w/cpp/algorithm/unique
    auto n = std::unique( std::begin(array), std::end(array) ) - std::begin(array) ; 
    for( auto i = 0 ; i < n ; ++i ) std::cout << array[i] << '\n' ;
}