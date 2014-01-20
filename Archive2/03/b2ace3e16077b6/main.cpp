#include <iostream>

int foo( int, int ) ; // declares that foo is a function
// it takes two parameters of type int and the result of evaluation is an int.

int main()
{
    int i ;
    i = 57 ; // std::cin >> i ; // say, 57

    int k = i+32 ; // k is initialized with the result of evaluation of i+32
    std::cout << k << '\n' ;

    int l = foo( i, 32 ) ; // l is initialized with the result of evaluation of foo( i, 32 )
    std::cout << l << '\n' ;

    // use the expression anonymously
    std::cout << i + 56 << '\n' ; // print the result of evaluation of i + 56

    // use the expression anonymously
    std::cout << foo( i, 56 ) << '\n' ; // result of evaluation of foo( i, 56 )
}

// define foo
int foo( int a, int b ) // a and b stand for the two integers that are pased too it
{
    int result = a + b ; // evaluate the result
    return result ; // and return it to the caller
}
