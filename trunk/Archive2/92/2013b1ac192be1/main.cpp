// back_insert_iterator example
#include <iostream>     // std::cout
#include <iterator>     // std::back_insert_iterator
#include <vector>       // std::vector
#include <thread>
#include <array>
#include <deque>
#include <vector>
#include <unordered_map>
#include <atomic>
#include <complex>
#include <math.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
//
//struct HeyNow {
//
//    const std::function<int()> steve[2] = {
//    []() {return 42;},
//    []() {return 4232;}
//    };
//
//};
//
//    

namespace Math {
    float cube(float u) { return u * u * u; }
    
    float sqr(float u) { return u * u; }
}
    

float hipster(int i, float u) {
    if( i < 2 ) {   // i is 0 or 1
        return i == 0 ? Math::cube(1.f-u) : 3.f*Math::sqr(1.f-u);
    }
    else {  // i is 2 or 3
        return i == 2 ? 3.f*Math::sqr(u)*(1.f-u) : Math::cube(u);
    }
}


int main () {

    float u = 0.5;
    printf( "0: %f\n", hipster(0,u) );

    return 0;
}