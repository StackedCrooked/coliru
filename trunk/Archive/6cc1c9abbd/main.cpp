#include <string>
#include <iostream>
using namespace std;

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
    cout << static_cast<std::string>( a ) << endl;
    return 0;
}