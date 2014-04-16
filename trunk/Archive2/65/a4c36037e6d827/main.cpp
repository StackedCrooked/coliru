#include <iostream>
namespace N {
   struct A;
}
void f( int );
void f( const N::A & );
struct N::A
{
   friend void f( int );
   friend void f( const N::A & );
};
namespace N {
   void g() { 
      f( 0 ); 
      f( A() );
   }
   void f( int ) { std::cout << "void N::f( int )" << std::endl; } 
   void f( const N::A & ) { std::cout << "void N::f( const A & )" << std::endl; }
}
void f( int ) { std::cout << "void ::f( int )" << std::endl; }
void f( const N::A & ) { std::cout << "void ::f( const A & )" << std::endl; }

int main() 
{
    N::g();
 
    return 0;
}