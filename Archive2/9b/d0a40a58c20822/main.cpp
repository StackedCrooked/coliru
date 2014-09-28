#include <iostream>
#include <type_traits>

template < typename T > const char* can_this_be_the_address_of_a( const void* address )
{
    const std::size_t alignment = std::alignment_of<T>::value ;
    const std::uintptr_t address_value = reinterpret_cast<std::uintptr_t>(address) ;
    return address_value%alignment == 0 ? "could be" : "can't be" ;
}

#define CAN_THIS_BE_THE_ADDRESS_OF_A( type, address ) ( \
    std::cout << #address << ' ' << can_this_be_the_address_of_a<type>(address) \
              << " the address of an object of type " << #type << '\n' )

int main()
{
    char c1 ='a', c2 = 'b' ;
    int i1 = 0, i2 = 0 ;
    double d1 = 0 ;

    CAN_THIS_BE_THE_ADDRESS_OF_A( int, &c1 ) ;
    CAN_THIS_BE_THE_ADDRESS_OF_A( double, &c1 ) << '\n' ;
    
    CAN_THIS_BE_THE_ADDRESS_OF_A( int, &c2 ) ;
    CAN_THIS_BE_THE_ADDRESS_OF_A( double, &c2 ) << '\n' ;
    
    CAN_THIS_BE_THE_ADDRESS_OF_A( int, &i1 ) ;
    CAN_THIS_BE_THE_ADDRESS_OF_A( double, &i1 ) << '\n' ;
    
    CAN_THIS_BE_THE_ADDRESS_OF_A( int, &i2 ) ;
    CAN_THIS_BE_THE_ADDRESS_OF_A( double, &i2 ) << '\n' ;
    
    CAN_THIS_BE_THE_ADDRESS_OF_A( int, &d1 ) ;
    CAN_THIS_BE_THE_ADDRESS_OF_A( double, &d1 ) << '\n' ;
}
