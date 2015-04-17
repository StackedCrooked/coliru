#include <iostream>
#include <signal.h>

int main() {
   
    std::cout << "This text is quite long and might as well be buffered" << std::endl;
    raise(SIGSEGV); // Oh dear.. segmentation violation
    std::cout << std::endl;
}