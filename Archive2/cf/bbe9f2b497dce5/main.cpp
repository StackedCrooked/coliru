#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <inttypes.h>

#define NUM_OF_READINGS 128

int main()
{
    
    static void (*changeRelayState)(void) = [] {
        std::cout << "hey" << std::endl;
    };

    changeRelayState();
    std::cout << "uffda" << std::endl;
}
