#include <atomic>
#include <iostream>
#include <cmath>

struct my_atomic_float
{
    static constexpr std::size_t digits_after_decimal = 6 ;
    static constexpr float scaling = 1000000.0 ;
    static constexpr long long scale( float f = 0 ) { return std::llround( f * scaling ) ; }
    
    std::atomic< long long > fixed_point ; 
    
    my_atomic_float( float f ) : fixed_point( scale(f) ) {}
    operator float() const { return fixed_point / scaling ; }
    my_atomic_float& operator+= ( float f ) { fixed_point += scale(f) ; return *this ;  }
    
    // etc.
};

std::ostream& operator<< ( std::ostream& stm, const my_atomic_float& f ) 
{ return stm << f.fixed_point / my_atomic_float::scaling ; }

// etc.

int main()
{
    my_atomic_float f(23.8) ;
    f += 2.3 ;
    std::cout << f << '\n' ;
}
