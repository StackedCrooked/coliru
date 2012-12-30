#include <iostream>

int main() {
    long long i = 20;
    loop:
    i += 20;
    for(int j = 2; j != 20; ++j)
        if(i % j != 0)
            goto loop;
    std::cout << i;
}