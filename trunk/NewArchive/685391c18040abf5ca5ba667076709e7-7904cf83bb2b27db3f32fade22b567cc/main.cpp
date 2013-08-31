#include <iostream>

int main()
{
    int i = 0x10000000;
    do {
        i += i;
        std::cout << i << std::endl;
    } while (i > 0);
    std::cout << i << std::endl;
}
