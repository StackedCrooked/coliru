#include <iostream>
#include <functional>

 void increment( int &count )
 {
   ++count;
 }
 
 template< class F, class A >
 void intermediate( F func, A arg )
 {
   func(arg);
 }
 
 int main()
 {
   int i = 0;
 
   intermediate( increment, i );
   std::cout << "Without std::ref => i="<< i << '\n';
 
   intermediate( increment, std::ref(i) );
   std::cout << "Using   std::ref => i="<< i << '\n';
 }