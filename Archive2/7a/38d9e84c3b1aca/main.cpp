#include <iostream>

int& prefix_plus_plus( int& a ) { a = a+1 ; return a ; } // result is an lvalue (returns reference to a)

int postfix_plus_plus( int& a ) // result is an rvalue (returns a temporary int)
{ int value_before_incr = a ;  a = a+1 ; return value_before_incr ; }

int main()
{
    int x ;
    
    x = 5 ; 
    std::cout << ++x << '\n' ; // 6 
    std::cout << x << '\n' ; // 6
    
    // behaves like :
    x = 5 ; 
    std::cout << prefix_plus_plus(x) << '\n' ; // 6 
    std::cout << x << '\n' ; // 6
    
    // behaves like :
    x = 5 ; 
    x = x+1 ;
    std::cout << x << '\n' ; // 6
    std::cout << x << '\n' ; // 6
    
    x = 5 ; 
    std::cout << x++ << '\n' ; // 5
    std::cout << x << '\n' ; // 6
    
    // behaves like :
    x = 5 ; 
    std::cout << postfix_plus_plus(x) << '\n' ; // 5 
    std::cout << x << '\n' ; // 6
    
    // behaves like :
    x = 5 ; 
    int anonymous_temporary = x ;
    x = x+1 ;
    std::cout << anonymous_temporary << '\n' ; // 5
    std::cout << x << '\n' ; // 6
}
