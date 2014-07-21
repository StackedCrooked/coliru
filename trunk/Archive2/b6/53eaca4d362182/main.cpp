#include <iostream>
#include <cstdlib>

int stuff();

int stuff() {
    std::cout << "lol\n";
    std::exit(EXIT_SUCCESS);
}

template<typename T>
T one_two() {
    std::cout << sizeof(T) << " is the size of this\n";
    std::exit(EXIT_SUCCESS);
}

int main() {
//    stuff();
    one_two<int>();
}
