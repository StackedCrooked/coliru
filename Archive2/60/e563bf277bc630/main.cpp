#include <iostream>
#include <string>
#include <algorithm>
#include <deque>
using namespace std ;

deque<int> add_numbers( string one, string two )
{
    static const std::string digits = "0123456789" ;
    std::size_t sz = std::max( one.size(), two.size() ) ;
    if( sz == 0 || // empty strings
        one.find_first_not_of(digits) != std::string::npos || // invalid characters
        two.find_first_not_of(digits) != std::string::npos ) return {0} ;

    // make the strings of the same size by adding zeroes at the front
    while( one.size() < sz ) one = '0' + one ;
    while( two.size() < sz ) two = '0' + two ;

    deque<int> result ; // the logic is much easier to follow
                         // with a deque and push_front

    int carry = 0 ;
    for( int i = sz-1 ; i >=0 ; --i )
    {
        // for this to work, both strings must be of the same size
        int sum = one[i] - '0' + two[i] - '0' + carry ;

        // push_front because we are comuting the less significant digit first
        result.push_front( sum % 10 ) ;

        carry = sum / 10 ;
    }

    if(carry) result.push_front(carry) ; // residual carry, if any

    return result ;
}

int main()
{
    for( int d : add_numbers( "987", "654321" ) ) std::cout << d ;
    std::cout << ' ' << 987+654321 << '\n' ;

    for( int d : add_numbers( "987654", "654321" ) ) std::cout << d ;
    std::cout << ' ' << 987654+654321 << '\n' ;
}
