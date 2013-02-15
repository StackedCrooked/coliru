#include <iostream>


template <typename T>
T Degrees ( T degrees ) {
    return (T)(degrees * 0.0174532925);
}

int main ( int argc, char* argv[] ) {
        
     std::cout << "Degrees: " << 180 << "\nRadians: " << Degrees<float>(180) << std::endl;
     Degrees<float> d = 45;
     auto r = 45+1;
    
     return 0;
}