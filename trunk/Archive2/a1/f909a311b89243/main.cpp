#include <iostream>

int main(int, char*[]) {
    int y = 10;
    int* x = &y;
    std::cout << x[0];
    return 0;
}