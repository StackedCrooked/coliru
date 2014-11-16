#include <iostream>

int main()
{

    constexpr auto upper_bound = 1'000'000'000'000 ; // C++14 literal
    constexpr auto lower_bound = -1'000'000'000'000 ;

    // integer_type is an alias for a signed integer type
    // which can hold integers with 13 decimal digits
    // http://www.stroustrup.com/C++11FAQ.html#decltype
    using integer_type = decltype(9'999'999'999'999) ;

    integer_type x = 0 ;
    std::cin >> x ; // if input fails, x would be set to zero
    integer_type y = 0 ;
    std::cin >> y ; // do nothing if std::cin is in a failed state

    if( x > lower_bound && y < upper_bound )
    {
        char relation = '=' ;
        if( x < y ) relation = '<' ;
        else if( y < x ) relation = '>' ;
        std::cout << x << ' ' << relation << ' ' << y << '\n' ;
    }
}
