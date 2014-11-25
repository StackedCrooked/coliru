#include <iostream>
#include <cctype>
#include <cassert>
#include <vector>
#include <algorithm>
#include <string>

int double_it( int digit )
{
    assert( digit >= 0 && digit <= 9 ) ; // 'if the user wants to use assertions'

    const int dbl[] = { 0, 2, 4, 6, 8, 1, 3, 5, 7, 9 } ;
    return dbl[digit] ;
}

 // from right to left, double every second number in the card
 // http://www.mochima.com/tutorials/vectors.html
 int sum_of_double_even_place_right_to_left( std::vector<int> digits ) // passed by value
 {
     // http://en.cppreference.com/w/cpp/algorithm/reverse
     std::reverse( digits.begin(), digits.end() ) ; // reverse the digits
     int sum = 0 ;

     // for every second digit, starting at position 1
     for( std::size_t i = 1 ; i < digits.size() ; i += 2 ) sum += double_it( digits[i] ) ;
     return sum ;
 }

 int sum_of_odd_places_right_to_left( std::vector<int> digits ) // passed by value
 {
     std::reverse( digits.begin(), digits.end() ) ; // reverse the digits
     int sum = 0 ;

     // for every second digit, starting at position 0
     for( std::size_t i = 1 ; i < digits.size() ; i += 2 ) sum += digits[i] ;
     return sum ;
 }

 bool final_sum_ends_in_zero( std::vector<int> digits )
 {
     const int final_sum = sum_of_double_even_place_right_to_left(digits) +
                           sum_of_odd_places_right_to_left(digits) ;
     return final_sum%10 == 0 ;
 }

 std::vector<int> string_to_vector( std::string digits )
 {
     std::vector<int> result ;

     for( char c : digits ) // http://www.stroustrup.com/C++11FAQ.html#for
     {
         // http://en.cppreference.com/w/cpp/string/byte/isdigit
         assert( std::isdigit(c) ) ; // 'if the user wants to use assertions'

         // http://en.cppreference.com/w/cpp/container/vector/push_back
         result.push_back( c - '0' ) ; // ( '6' - '0' ) == 6 etc.
     }

     return result ;
 }


int main()
{
    const std::string card = "4388576018402626" ;
    std::cout << std::boolalpha << "final_sum_ends_in_zero? "
              << final_sum_ends_in_zero( string_to_vector(card) ) << '\n' ;
}
