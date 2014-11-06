#include <iostream>
#include <memory>

namespace creator
{
    template < typename T, typename... ARGS >
    std::unique_ptr<T> make_unique( ARGS&&... args )
    { return std::unique_ptr<T>( new T( std::forward<ARGS>(args)... ) ) ; }
}

int main()
{
    struct A
    {
        A() { std::cout << this << " - A::default_constructor\n" ; }

        A( int i, double d = 2.3, const char* cstr = "hello" )
        { std::cout << this << " - A::A( " << i << ", " << d << ", '" << cstr << "' )\n" ; }

        ~A() { std::cout << this << " - A::destructor\n" ; }
    };

    auto pa1 = creator::make_unique<A>() ;
    auto pa2 = creator::make_unique<A>(1) ;
    auto pa3 = creator::make_unique<A>( 22, 33.44 ) ;
    auto pa4 = creator::make_unique<A>( 333, 555.666, "bye" ) ;

    std::cout << "\nexit main\n\n" ;
}
