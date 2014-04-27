#include <vector>
#include <iostream>
#include <algorithm>

void palindrome( std::vector<int> );

int main()
{
    int x;
    std::vector<int> values ;
    
    std::cout << "enter your numbers (end with a non-digit): ";
    
    // http://en.cppreference.com/w/cpp/container/vector/push_back
    while( std::cin >> x ) values.push_back(x) ;  

    palindrome(values);
}

void palindrome( std::vector<int> vect )
{
    for( int v : vect ) std::cout << v << ' ' ;
    
    // http://en.cppreference.com/w/cpp/algorithm/equal
    if( std::equal( vect.begin(), vect.begin() + vect.size()/2, vect.rbegin() ) )
       std::cout << " <== palindrome\n" ;
    else std::cout << "<== not palindrome\n" ;

}