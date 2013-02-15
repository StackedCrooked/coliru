#include <iostream>

int main() {
    int* array = new int[15];
    for(int i = 0; i < 15; ++i) {
        array[i] = i;
    }
    for(int i = 0; i < 15; ++i)
        std::cout << array[i] << '\n';
    delete[] array;
}