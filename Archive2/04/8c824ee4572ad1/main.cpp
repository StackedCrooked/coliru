#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
    const auto print = []( const std::vector<int>& seq )
    {
        for( std::size_t i = 40 ; i > seq.size() ; --i ) std::cout << ' ' ;
        for( int digit : seq ) std::cout << digit ;
        std::cout << '\n' ;
    };

    const std::vector<int> a { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0,
                               1, 2, 3, 4, 5, 6, 7, 8, 9, 0,
                               1, 2, 3, 4, 5, 6, 7, 8, 9, 0 } ;
    print(a) ;

    const std::vector<int> b( a.size()/2, 9) ;
    print(b) ;

    // a + b

    // step 1. make reverse of a and b
    std::vector<int> rev_a( a.rbegin(), a.rend() ) ;
    std::vector<int> rev_b( b.rbegin(), b.rend() ) ;

    // step 2. make them of the same size by adding zeroes at the end
    const std::size_t sz = std::max( a.size(), b.size() ) ;
    rev_a.resize(sz) ;
    rev_b.resize(sz) ;

    std::vector<int> result ;

    // step 3. add digit by digit with carry and push back into result
    int carry = 0 ;
    for( std::size_t i = 0 ; i < sz ; ++i )
    {
        const int sum = rev_a[i] + rev_b[i] + carry ;
        carry = sum / 10 ;
        result.push_back( sum % 10 ) ;
        //std::cout << a[i] << ' ' << b[i] << ' ' << sum << '\n' ;
    }
    while( carry > 0 ) { result.push_back( carry%10 ) ; carry /= 10 ; }

    // step 4. reverse the result to get the answer
    std::reverse( result.begin(), result.end() ) ;

    print(result) ;
}
