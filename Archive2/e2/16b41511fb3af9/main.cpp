#include <iostream>

#define ROUND(a) ((int)(a+.5))

int main() {
    std::cout << ROUND(1 << 2);   
}