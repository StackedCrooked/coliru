#include <iostream>

int * get_zero_array() {
    int array[3];
    for (int i = 0; i < 3; ++i)
        array[i] = 0;
    return array;
}

int main() {
    int *a = get_zero_array();
    std::cout << a[0] << std::endl;
}
