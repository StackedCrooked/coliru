#include <iostream>
#include <memory>
#include <type_traits>

template< typename T, typename U >
typename std::enable_if< std::is_polymorphic<U>::value, T& >::type
dynamic_deref( const std::unique_ptr<U>& p )
{
    if(p) return dynamic_cast<T&>( *p ) ;
    throw std::invalid_argument( "nullptr" ) ;
}

struct A { virtual ~A() {} } ;
struct B : virtual A {} ;
struct C : virtual A { C( int v ) : c(v) {} const int c ; } ;
struct D : B, C { D( int i ) : C(i) {} } ;

int main()
{

    try
    {
        std::unique_ptr<A> pa( new D(99) ) ;
        std::cout << "try down-cast A => C: " ;
        C& rc = dynamic_deref<C>(pa) ;
        std::cout << "ok. rc.c == " << rc.c << '\n' ;

        std::unique_ptr<B> pb( new D(1234) ) ;
        std::cout << "try cross-cast B => C: " ;
        C& rc1 = dynamic_deref<C>(pb) ;
        std::cout << " ok. rc1.c == " << rc1.c << '\n' ;

        pb.reset( new B ) ;
        std::cout << "try cross-cast B => C: " ;
        C& rc2 = dynamic_deref<C>(pb) ;
        std::cout << " ok. rc2.c == " << rc2.c << '\n' ;
    }

    catch( const std::exception& e )
    {
        std::cout << "error: " << e.what() << '\n' ;

        try
        {
            std::unique_ptr<A> pa ;
            std::cout << "try down-cast A => C: " ;
            C& rc = dynamic_deref<C>(pa) ;
            std::cout << " ok. rc.c == " << rc.c << '\n' ;
        }

        catch( const std::exception& e )
        {
            std::cout << "error: " << e.what() << '\n' ;
        }
    }
}
