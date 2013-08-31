#include <iostream>
#include <type_traits>
#include <stdexcept>

struct SoDirty {
    int* radioactive;
    bool deletable;
    
    SoDirty () : radioactive(nullptr), deletable(true) {
        
    }
    
    SoDirty ( int a ) : SoDirty() {
        static int x;
        radioactive = &x;
        //throw std::runtime_error("Leak "); // invariants broken here => not exception-safe 
        deletable = false;
    };
    
    SoDirty ( double a ) {
        radioactive = &x;
        throw std::runtime_error("Leak "); // invariants broken here => who the hell cares?
        deletable = false
    };
    
    ~SoDirty () {
        std::cout << "NOPE! - ";
        std::cout << *radioactive;
        std::cout << ": Yaahnn, we can use raw resources~~~~" << std::endl;
        if(deletable) delete radioactive;
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