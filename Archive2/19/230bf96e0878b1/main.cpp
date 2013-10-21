#include <iostream>
#include <type_traits>

class myClass
{
    public :
        template < typename  T > inline static
            typename std::enable_if< std::is_unsigned<T>::value, bool >::type
                isNbrOdd( T nbr ) ;

        template < typename  T > inline static
            typename std::enable_if< !std::is_unsigned<T>::value, bool >::type
                isNbrOdd( T nbr ) ;
};

template < typename  T >
    typename std::enable_if< std::is_unsigned<T>::value, bool >::type
        myClass::isNbrOdd( T nbr ) { return nbr%2 ; }

template < typename  T >
    typename std::enable_if< !std::is_unsigned<T>::value, bool >::type
        myClass::isNbrOdd( T )
        {
            std::cout << "please use an unsigned integral type\n" ;
            return false ;
        }

int main()
{
    std::cout << std::boolalpha ;

    std::cout << "unsigned long long: " << myClass::isNbrOdd( 79ULL ) << "\n\n" ;

    std::cout << "double: " << myClass::isNbrOdd( 79.0 ) << "\n\n" ;

    unsigned short s = 79 ;
    std::cout << "unsigned short: " << myClass::isNbrOdd(s) << '\n' ;
}
