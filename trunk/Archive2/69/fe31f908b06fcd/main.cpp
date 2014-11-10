#include <iostream>

int main() {
    int x;
    x = 5;
    x -= x - --x;   
    std::cout << x;
}