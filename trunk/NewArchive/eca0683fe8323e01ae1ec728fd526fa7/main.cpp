#include <iostream>


template <typename T>
T degrees() {
    return (T)(degrees * 0.0174532925);
}

int main ( int argc, char* argv[] ) {
        
     std::cout << "Degrees: " << 60 << "\nRadians: " << degrees<float>(180) << std::endl;
    
     return 0;
}