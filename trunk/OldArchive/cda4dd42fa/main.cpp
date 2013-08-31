#include <string>
#include <iostream>

class value {
public:
    template <typename T>
    value(const T &t) {
    }
    
    template <typename T>
    operator T( void ) const {
        T t;
        return t;
    }
};

int main( void ) {
    value a( std::string( "A" ) );
    std::cout << static_cast<std::string>( a ) << std::endl;
    return 0;
}