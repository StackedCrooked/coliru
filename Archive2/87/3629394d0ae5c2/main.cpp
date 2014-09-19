


#include <cstdio>
#include <vector>
#include <string>
#include <functional>
#include <iostream>


int main()
{
   typedef std::string T;
   typedef std::reference_wrapper<T>  RefT;
   
   std::string t0 = "Hi";
   std::string t1 = "Hello";
   std::string t2 = "Bye!";
   
   std::vector<RefT> v;
   
   v.reserve(3);
   
   v.push_back( std::ref(t0) );
   
   v.push_back( std::ref(t1) );
   
   v.push_back( std::ref(t2) );
   
   
   t2 = "World";
   
   
   for( auto & e: v )
   {
    std::string & s = e;
    std::cout << s << std::endl;
   }
   
  
}