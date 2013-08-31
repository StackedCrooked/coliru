#include <iostream>
#include <type_traits>
#include <stdexcept>

struct SoDirty {
    int* radioactive;
    
    SoDirty () : radioactive(nullptr) {
        
    }
    
    SoDirty ( int a ) : SoDirty() {
        radioactive = new int( a );
        throw std::runtime_error("Leak ");
    };
    
    SoDirty ( double a ) {
        radioactive = new int( (int)a );
        throw std::runtime_error("Leak ");
    };
    
    ~SoDirty () {
        std::cout << "NOPE! - ";
        std::cout << *radioactive;
        std::cout << ": Yaahnn, we can use raw resources~~~~" << std::endl;
        delete radioactive;
    }
};

int main() {
    try {
        SoDirty ahh( 24.0 );
    }
    catch ( ... ) {
        std::cout << "Caught!" << std::endl;
    }
    try {
        SoDirty ahh( 25 );
    }
    catch ( ... ) {
        std::cout << "Caught!" << std::endl;
    }
}