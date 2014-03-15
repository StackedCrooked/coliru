#include <iostream>

int main()
{
    std::cout << "hi :)" << std::endl;
}

// let's sabotage this program by introducing UB muahaha
#define long short
