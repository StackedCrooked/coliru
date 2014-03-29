#include <iostream>
#include <sstream>

void show_results( std::ios& stm )
{
    std::cout << std::boolalpha << "bad: " << stm.bad() << "   fail: " << stm.fail()
               << "   eof: " << stm.eof() << "   good: " << stm.good()
               << "   bool(stm): " << bool(stm) << "   !stm: " << !stm << '\n' ;
}

int main()
{
   std::istringstream stm( "123 456" ) ;
   int i ;

   stm >> i ;
   show_results( stm ) ;
   // bad: false   fail: false   eof: false   good: true   bool(stm): true   !stm: false

   stm >> i ;
   show_results( stm ) ;
   // bad: false   fail: false   eof: true   good: false   bool(stm): true   !stm: false

   stm >> i ;
   show_results( stm ) ;
   // bad: false   fail: true   eof: true   good: false   bool(stm): false   !stm: true
}
