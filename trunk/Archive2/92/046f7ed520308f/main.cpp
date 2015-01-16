#include <iostream>
#include <type_traits>

extern double c[][3]; // the (incomplete) type of c is array of unknown size int[3] 
extern const std::size_t sz ;

int main()
{
    static_assert( !std::is_same< decltype(c), double (*)[3] >::value, "can't be the same type" ) ;
    static_assert( std::is_array< decltype(c) >::value, "must be an array type" ) ;
    static_assert( !std::is_pointer< decltype(c) >::value, "can't be a pointer" ) ;
    
    // std::cout << sizeof(c) << '\n' ; // *** error: size of incomplete type
    std::cout << "sz: "  << sz << '\n' ; // fine
}

double c[100][3]{}; // the (complete) type of c is array of 100 int[3] 

const std::size_t sz = sizeof(c)  ; // fine: c is of a complete type now
