#include <iostream>

template < typename T, int& N >
T fixed_multiply( T val )
{
    int result = val * N ;
    N += 5 ;
    return result ;
}

int multiplier = 3 ;

int foo( int arg ) { return fixed_multiply<int,multiplier>(arg) ; }

int main()
{
  std::cout << foo(10) << '\n'; // 30
  std::cout << foo(10) << '\n'; // 80
  multiplier = -9 ;
  std::cout << foo(10) << '\n'; // -90
}
