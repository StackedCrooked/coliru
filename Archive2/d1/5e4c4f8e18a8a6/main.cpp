#include <typeinfo>

class polymorphic_erasure {
    void const * ptr;
    void (* [[noreturn]] throw_self)( void const * );

public:
    template< typename static_type >
    polymorphic_erasure( static_type & o )
        : ptr( static_cast< void const * >( & o ) )
        , throw_self( []( void const * p ) {
            throw const_cast< static_type * >(
                static_cast< static_type const * >( p ) );
        } )
        {}

    polymorphic_erasure()
        : ptr( nullptr )
        , throw_self( []( void const * ) { throw std::bad_cast(); } )
        {}

    template< typename want_type >
    want_type & get() const {
        try {
            throw_self( ptr );
        } catch ( want_type * result ) {
            return * result;
        } catch ( ... ) {}
        throw std::bad_cast();
    }
};

#include <iostream>
#include <sstream>

int main() {
    int const i = 3;
    polymorphic_erasure e = i;
    
    std::cout << e.get< int const >() << '\n';
    
    try {
        e.get< int >();
    } catch (...) {
        std::cout << "can't add const\n";
    }
    
    std::stringstream ss;
    e = ss;
    
    e.get< std::ostream >() << "hello";
    std::cout << ss.rdbuf() << '\n';
}