#include <type_traits>
#include <cstddef>
#include <array>
#include <cmath>
#include <iostream>

struct f;

template <typename T>
f dirty1( T t ) {
    return f( t );
}

template <typename T>
void dirty2( T t ) {
    auto usef = f( t );
}

struct f {
   int a;
   
   f( int a = 0 ) : a( a ) {
       
   }
};

int main () {
   
}