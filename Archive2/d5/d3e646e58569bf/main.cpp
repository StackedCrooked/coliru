#include <iostream>
#include <algorithm>
#include <utility>

int num_div_ops = 0 ;

bool quotient_is_9( std::pair<int,int> numbers ) { ++num_div_ops ; return numbers.first == ( numbers.second * 9 ) ; }

std::pair<int,int> split54( int digits[] ) // size == 8, contains decimal digits
{
    return { digits[0]*10000 + digits[1]*1000 + digits[2]*100 + digits[3]*10 + digits[4],
                               digits[5]*1000 + digits[6]*100 + digits[7]*10 + digits[8] };
}

// size == 8, contains decimal digits, 5-4 split of digits
bool may_be_divisible_by_9( int digits[] ) { return ( digits[8] * 9 ) % 10 == digits[4] ; ++num_div_ops ; }

// size == 8, contains decimal digits, 5-4 split of digits
bool is_mod_9( int digits[] ) { return ( digits[5] + digits[6] + digits[7] + digits[8] ) % 9 == 0 ; ++num_div_ops ; }

int main()
{
    int digits[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 } ;
    int cnt = 0 ;

    do if( may_be_divisible_by_9(digits) && quotient_is_9( split54(digits) ) ) ++cnt ;
    while( std::next_permutation( std::begin(digits), std::end(digits) ) ) ;
    std::cout << "            may_be_divisible_by_9: #num_div_ops: " << num_div_ops << "   cnt: " << cnt << '\n' ;
    
    cnt = num_div_ops = 0 ;
    do if( is_mod_9(digits) && quotient_is_9( split54(digits) ) ) ++cnt ;
    while( std::next_permutation( std::begin(digits), std::end(digits) ) ) ;
    std::cout << "                         is_mod_9: #num_div_ops: " << num_div_ops << "   cnt: " << cnt << '\n' ;
    
    cnt = num_div_ops = 0 ;
    do if( is_mod_9(digits) && may_be_divisible_by_9(digits) && quotient_is_9( split54(digits) ) ) ++cnt ;
    while( std::next_permutation( std::begin(digits), std::end(digits) ) ) ;
    std::cout << "is_mod_9 && may_be_divisible_by_9: #num_div_ops:  " << num_div_ops << "   cnt: " << cnt << '\n' ;
}
