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
        
     Degrees<float> half_circle(180);
     Degrees<float> full_circle = half_circle * 2;
     
     std::cout << "A full circle has " << full_circle << " radians\n";
    
     return 0;
}