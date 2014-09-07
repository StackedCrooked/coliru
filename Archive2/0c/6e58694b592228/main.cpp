#include <iostream>

struct A 
{
   A() { std::cout << "constructor(" << this << ")\n" ; }
   ~A() { std::cout << "destructor(" << this << ")\n" ; }
  int foo() { static int i = 0 ; return ++i ; }
};


int main()
{
    std::cout << ( ( ( A().foo() + A().foo() + A().foo() ) * A().foo() ), "hello " )
              << "world " << ( A().foo(), '!' ) << '\n' ; 
}