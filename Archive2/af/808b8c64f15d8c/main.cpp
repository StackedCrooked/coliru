#include <iostream>

#define TRACE_1(y) std::cout << y;
#define TRACE_BLA(y) 
#define TRACE_I(x,y) TRACE_ ## x (y)
#define TRACE(x,y) TRACE_I(x,y)

int main()
{
    TRACE(BLA,"abc") // "abc" won't be printed, as BLA is not defined
    #undef BLA
    TRACE(BLA,"abc") // "abc" won't be printed, as BLA is not defined
    #define BLA 1
    TRACE(BLA,"xyz") // "xyz" will be printed, as BLA is a defined symbol
    #undef BLA
    TRACE(BLA,"abc") // "abc" won't be printed, as BLA is not defined
}
