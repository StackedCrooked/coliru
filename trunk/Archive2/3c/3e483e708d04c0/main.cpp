#include <iostream>
using namespace std;

#define A
#define B

int main() {
    #ifdef A
    std::cout << "a ";
    #endif

    #ifdef B
    std::cout << "b ";
    #endif

    #ifdef C
    std::cout << "c ";
    #endif

    #ifdef B C
    std::cout << "bc ";
    #endif

    #ifdef C B
    std::cout << "cb ";
    #endif

    return 0;
}