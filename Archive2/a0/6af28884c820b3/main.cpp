#include <iostream>

int main() {
    for (int i = 10; i < 50; i += 10)
        for (int j = 1; j < 6; j++)
            std::cout << (i + j) << ' ';
}