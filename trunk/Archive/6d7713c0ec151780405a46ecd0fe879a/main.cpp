#include <iostream>


template <typename T>
struct Degrees {
    
    T degrees;
    
    Degrees ( T degs ) : degrees(degs) {
        
    }
    
    operator T () {
        return (T)(degrees * 0.0174532925);
    }
    
};

int main ( int argc, char* argv[] ) {
        
     std::cout << "Degrees: " << 60 << "\nRadians: " << Degrees<float>(180) << std::endl;
    
     return 0;
}