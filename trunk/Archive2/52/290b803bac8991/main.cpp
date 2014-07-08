#include <iostream>

int main() {
    for (int i = -2; i < 128; ++i)
        std::cout << ((char) i);
}