#include <iostream>

int g_arr[] = {1, 2, 3};

void foo(int *&arr) {
    delete[] arr;
    arr = g_arr;   
}

int main() {
    int *arr = new int[3]{4, 5, 6};
    foo(arr);
    
    for (int i = 0; i < 3; ++i) {
        std::cout << arr[i] << '\n';
    }
}