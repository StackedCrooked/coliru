#include <iostream>
#include <limits>

int main() 
{
    long long v = std::numeric_limits<unsigned int>::max() + 0xf0000001LL ;
	unsigned int u ;
    int i ;
    
    u = v ; // narrowing; destination type is unsigned, the resulting value is v % 2^n
            // where n is the number of bits used to represent unsigned int (0xf0000000)
    
    i = v ; // narrowing; destination type is signed, the value is implementation-defined 
            // may be (usually is) v % 2^n interpreted as a signed value
    
	std::cout << u << ' ' << i << ' ' << 0xf0000000LL << '\n' ;
    
    double f = v ;
    
    bool b = f ; // non-zero, true
    
    u = f ; // floating point to integral conversiopn; value (after discarding fractional part) 
            // can't be represented in the integral type; undefined behaviour
    
    i = f ; // floating point to integral conversiopn; value (after discarding fractional part) 
            // can't be represented in the integral type; undefined behaviour

    std::cout << std::boolalpha << b << ' ' << u << ' ' << i << '\n' ;
}
