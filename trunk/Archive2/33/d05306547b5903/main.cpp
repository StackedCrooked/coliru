#include <iostream>

int main() {
    int x[] = {1, 2, 3, 4};
    for (int i : x)
        std::cout << i;
    return 0; 
}