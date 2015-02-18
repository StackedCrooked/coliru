#include <iostream>

int main() {
    #ifdef _REENTRANT
        std::cout << "pthreads\n";
    #else
        std::cout << "no threads\n";
    #endif
}
