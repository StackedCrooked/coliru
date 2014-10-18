#include <iostream>
#include <cassert>

int main() {
    int i = 1;
    int c = 0;

    do {
        c ++;
        i += i;

        assert(i >= 0);

        std::cout << i << std::endl;
    } while (i >= 0);

    std::cout << c << std::endl;

    return 0;
}