#ifdef _cplusplus

// c++ hello world
#include <iostream>

int main() {
    std::cout << "Hello world\n";
    return 0;
}

#else

// c hello world
#include <stdio.h>
int main(void) {
    printf("Hello world\n");
    return 0;
}

#endif