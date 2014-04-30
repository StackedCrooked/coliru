#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <strings.h>
#include <functional>
#include <exception>

using namespace std;

template< typename T1, typename T2, typename R, typename F>
 inline std::vector< R> zip( const std::vector< T1> & v1, const std::vector< T2> & v2, F f) {
     if( v1.size() != v2.size())
         throw 1;
         //throw exception( "Bad length!");

     typename std::vector< T2>::const_iterator it2 = v2.begin();
     std::vector< R> res;

     for( typename std::vector< T1>::const_iterator it1 = v1.begin();
                                                    it1!= v1.end();
                                                  ++it1)
     {
         res.push_back( f( *it1, *it2));
       ++it2;
     }

     return res;
 }

class C {
public:
    static  C* foo( const C* c1, const C* c2) {
                return new C;
            }
};

std::vector< C*>  sum( const std::vector< C*> &v1, const std::vector< C*> &v2)
{
    return zip< C*, C*, C*>( v1, v2, C::foo);
}

int main() {
  

}