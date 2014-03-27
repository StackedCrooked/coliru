#define STRINGIFY(...) #__VA_ARGS__

#include <iostream>

int main() {
    std::cout << STRINGIFY([]{
        return main;
    });
}