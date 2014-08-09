#include <iostream>
#define TESTING

int main() {
    #if defined(TESTING) && (TESTING == 1)
    std::cout << "testing";
    #endif
}