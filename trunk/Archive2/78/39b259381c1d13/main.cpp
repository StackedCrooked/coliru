#include <iostream>

void foo(int *&arr) {
    delete[] arr;
    arr = new int[3]{1, 2, 3};
}

int main() {
    int *arr = new int[3]{4, 5, 6};
    foo(arr);
    
    for (int i = 0; i < 3; ++i) {
        std::cout << arr[i] << '\n';
    }
}