#include <vector>
#include <iostream>
#include <algorithm>

bool palindrome( const std::vector<int>& );

int main()
{
    int x;
    std::vector<int> values ;
    
    std::cout << "enter your numbers (end with a non-digit): ";
    
    // http://en.cppreference.com/w/cpp/container/vector/push_back
    while( std::cin >> x ) values.push_back(x) ;  
    
    for( int v : values ) std::cout << v << ' ' ;

    if( palindrome(values) ) std::cout << " is a palindrome.\n" ;
    else std::cout << "is not palindromic.\n" ;
}

bool palindrome( const std::vector<int>& vect )
{
    // http://en.cppreference.com/w/cpp/algorithm/equal
    return std::equal( vect.begin(), vect.begin() + vect.size()/2, vect.rbegin() ) ;
}