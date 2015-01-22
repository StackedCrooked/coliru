#include <iostream>

enum pythag_result_type { YES, NO, INVALID_DATA };

// you may want to ignore this for the present
// we can get equivalent output by writing the switch-case in main
// this overloads the stream insertion operator for pythag_result_type
std::ostream& operator << ( std::ostream& stm, pythag_result_type result ) ;

pythag_result_type check_pythag( int a, int b, int c )
{
    // invalid if any side is non-positive
    if( (a<=0) || (b<=0) || (c<=0) ) return INVALID_DATA ;

    // make a the largest of the three sides
    if( a < b ) std::swap(a,b) ; // a is now that larger of(a,b), and b is the smaller of of(a,b)
    if( a < c ) std::swap(a,c) ; // a is now that largest of(a,b,c)

    if( a >= (b+c) ) return INVALID_DATA ; // not sides of a triangle

    return a*a == b*b + c*c ? YES : NO ;
}

int main()
{
    const pythag_result_type result = check_pythag( 20, 15, 25 ) ;
    switch(result) // switch on result
    {
        case YES: std::cout << "Yes\n" ; break ;
        case NO:  std::cout << "No\n" ; break ;
        default: std::cout << "Invalid data\n" ;
    } // Yes

    std::cout << check_pythag( -4, 3, 5 ) << '\n' // Invalid data
              << check_pythag( 4, 0, 4 ) << '\n' // Invalid data
              << check_pythag( 21, 220, 221 ) << '\n' // Yes
              << check_pythag( 4, 3, 5 ) << '\n' // Yes
              << check_pythag( 6, 3, 5 ) << '\n' // No
              << check_pythag( 4, 1, 5 ) << '\n' ; // Invalid data

}

// overloaded stream insertion operator for pythag_result_type
std::ostream& operator << ( std::ostream& stm, pythag_result_type result )
{
    switch(result)
    {
        case YES: return stm << "Yes" ;
        case NO:  return stm << "No" ;
        default: return stm << "Invalid data" ;
    }
}
