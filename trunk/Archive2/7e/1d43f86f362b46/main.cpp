#include <iostream>
#include <type_traits>
using namespace std;

   /** Greates common divisor */
   template<bool argsPositive = false,
            typename T,
            typename std::enable_if<std::is_integral<T>::value>::type * = nullptr
            >
    T gcd2( T  a, T  b )
    {

        if(!argsPositive){
            a = std::abs( a );
            b = std::abs( b );
        }

        if( a == 0  ||  a == b ){
            return  b;
        }
        if( b == 0 ){
            return  a;
        }
        if( a > b ){
            return  gcd2<true,T>( a % b, b );
        }
        else{
            return  gcd2<true,T>( a, b % a );
        }
    }
    
    
   /** Greates common divisor */
   template<bool argsPositive = false,
            typename T
            >
     typename std::enable_if<std::is_integral<T>::value,T >::type gcd22( T  a, T  b )
    {

        if(!argsPositive){
            a = std::abs( a );
            b = std::abs( b );
        }

        if( a == 0  ||  a == b ){
            return  b;
        }
        if( b == 0 ){
            return  a;
        }
        if( a > b ){
            return  gcd2<true,T>( a % b, b );
        }
        else{
            return  gcd2<true,T>( a, b % a );
        }
    }

int main() {
    // your code goes here
    int a;
	
	gcd2(a,a);
	gcd22(a,a); // does not compile under clang
	
	return 0;
}