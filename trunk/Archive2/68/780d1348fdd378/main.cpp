#include <iostream>

int& prefix_plus_plus( int& a ) // result is an lvalue (returns reference to a)
{ a = a+1 ; return a ; }

int postfix_plus_plus( int& a ) // result is an rvalue (returns a temporary int)
{ 
    const int value_before_incr = a ;  // value computation
    a = a+1 ; // side effect
    return value_before_incr ; // return computed value
}

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
    
    // -----------------------------------------------
    
    x = 5 ; 
    std::cout << x++ << '\n' ; // 5 (value compuation yields 5)
    std::cout << x << '\n' ; // 6 (side effect has incremented x)
    
    // behaves like :
    x = 5 ; 
    std::cout << postfix_plus_plus(x) << '\n' ; // 5  (value compuation yields 5)
    std::cout << x << '\n' ; // 6 (side effect has incremented x)
    
    // behaves like :
    x = 5 ; 
    const int anonymous_oomputed_value = x ; // value computation yields 5
    x = x+1 ; // side effect increments x
    std::cout << anonymous_oomputed_value << '\n' ; // 5
    std::cout << x << '\n' ; // 6
}
