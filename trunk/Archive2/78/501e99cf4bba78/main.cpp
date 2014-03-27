#define STRINGIFY(...) R ## #__VA_ARGS__

#include <iostream>

int main() {
    std::cout << STRINGIFY([]{
        return main;
    })";
}