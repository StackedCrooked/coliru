#include <iostream>

int main() {
    char x[] = "Hello";
    
    std::size_t e = sizeof(x) - 2;
    for (std::size_t b = 0; b <= (e / 2); ++b, --e) {
        char tmp = x[b];
        x[b] = x[e];
        x[e] = tmp;
    }
    
    std::cout << x;

    return 0;
}