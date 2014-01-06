#include <iostream>
#include <type_traits>
#include <utility>
#include <typeinfo>

template< typename T, bool >
class value_wrapper
{
private:
    T t_;

public:
    explicit value_wrapper( T&& t )
        : t_( std::move( t ) )
    {
        std::cout << "rvalue " << typeid( t_ ).name() << std::endl;
    }
    
    const T& cref() const { return t_; }
};

template<typename T>
struct value_wrapper< T, true > // specialization for lvalue references
{
private:
    const T& t_;

public:
    explicit value_wrapper( const T& t )
        : t_( t )
    {
        std::cout << "lvalue " << typeid( t_ ).name() << std::endl;
    }

    const T& cref() const { return t_; }
};

template< typename T >
using helper = value_wrapper< typename std::decay< T >::type, 
                              std::is_lvalue_reference< T >::value >;

template< typename T >
helper< T > wrap( T&& t )
{
    return helper< T >( std::forward< T >( t ) );
}

template< typename T, bool BL, bool BR >
bool operator==( const value_wrapper< T, BL >& lhs, const value_wrapper< T, BR >& rhs )
{
    return lhs.cref() == rhs.cref();
}

int f() { return 1; }

int main()
{
    int i = 1;
    wrap( i );
    const int ci = 1;
    wrap( ci );
    wrap( 1 );
    wrap( f() );
    
    if( wrap( i ) == wrap( 1 ) ) {
        std::cout << "OK" << std::endl;
    }
    if( wrap( i ) == wrap( 2 ) ) {
        std::cout << "not OK" << std::endl;
    }
}
