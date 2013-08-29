#include <iostream>
#include <string>
#include <vector>


template <typename T>
T get () {
    std::cout << "get<>()" << std::endl;
    return T();
}


float get () {
    std::cout << "get()" << std::endl;
    return 0.13;
}


int main() {
    get<int>();
    get();
}