#include <iostream>

template <typename T>
T as_radians(T t) {
    return (T)(t * 0.0174532925);
}

int main () {
     std::cout << "A full circle has " << as_radians<float>(360) << " radians\n";
    
     return 0;
}