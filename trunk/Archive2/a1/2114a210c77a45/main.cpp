#include <typeinfo>
#include <functional>

class polymorphic_erasure {
    std::function< void() > throw_self;

public:
    template< typename static_type >
    polymorphic_erasure( static_type & o )
        : throw_self( [ & o ] { throw & o; } )
        {}

    polymorphic_erasure()
        : throw_self( [] { throw std::bad_cast(); } )
        {}

    template< typename want_type >
    want_type & get() const {
        try {
            throw_self();
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