#include <iostream>

template <size_t N>
void printArray(int (&a)[N]) {
    for (int i : a) {
        std::cout << i << " ";
    }
}

int main() {
    int a[] = { 1, 2, 3, 4, 5 };
    printArray(a);
}