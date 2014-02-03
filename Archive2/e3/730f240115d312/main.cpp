#include <iostream>
#include <cstdint>

std::uintptr_t numeric_value( const void* ptr ) 
{ return reinterpret_cast<std::uintptr_t>(ptr) ; }

template < typename T > void test()
{
    std::cout << "size of object is: " << sizeof(T) << '\n' ;
    
    T array[4] ; // array of 4 objects
    
    // print out the last three digits of the numeric value of the addresses
    for( int i = 0 ; i < 4 ; ++i ) std::cout << numeric_value( std::addressof(array[i]) ) % 1000 << ' ' ;
    std::cout << '\n' ;
    
    T* p = std::addressof(array[0]) ; // points to element at position zero
    std::cout << numeric_value(p) % 1000 << ' ' ; // print out last three digits of its numeric value
    
    ++p ; // increment it
    std::cout << numeric_value(p) % 1000 << ' ' ; // print out last three digits of its numeric value

    ++p ; // increment it
    std::cout << numeric_value(p) % 1000 << ' ' ; // print out last three digits of its numeric value

    ++p ; // increment it
    std::cout << numeric_value(p) % 1000 << ' ' ; // print out last three digits of its numeric value
    
    std::cout << "\n------------------------------\n" ;
}

int main()
{
    test<int>() ;
    test<long>() ;
    test<long double>() ;
    test< char[32] >() ;
    test< char[27] >() ;
}
