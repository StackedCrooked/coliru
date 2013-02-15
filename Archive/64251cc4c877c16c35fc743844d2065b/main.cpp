#include <iostream>

int main() {
    int i = 5;
    goto foo;
    
    for (i = 0; i < 10; ++i) {
        foo:;
        std::cout << i << '\n';
    }
}