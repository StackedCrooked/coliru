#include <iostream>

#define BUILDTIME __DATE__ " " __TIME__

int main() {
    std::cout << BUILDTIME << std::endl;
    const char * test = BUILDTIME;
    std::cout << test << std::endl;
}