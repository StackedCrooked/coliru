#include <iostream>

int main() {
    size_t a = 10;
    size_t b = 11;
    while(b < 20) {
        if((a % b) == 0)
            b++;
        else {
            a++;
            b = 11;
        }
    }
    std::cout << a;
}