#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

int main()
{
    // sort a single string
    std::string text = "Michael" ;
    std::sort( text.begin(), text.end() ) ;
    std::cout << text << '\n' ;

    // sort an array of strings
    std::string array[5] { "zero", "one", "two", "three", "four" } ;
    std::sort( array, array+5 ) ;
    for( const auto& str : array ) std::cout << str << ' ' ;
    std::cout << '\n' ;

    // sort a vector of strings
    std::vector<std::string> vec { "five", "six", "seven", "eight", "nine" };
    std::sort( vec.begin(), vec.end() ) ;
    for( const auto& str : vec ) std::cout << str << ' ' ;
    std::cout << '\n' ;
}
