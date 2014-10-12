#include <iostream>

class A {
public:
    static int arr[][3];
};


int main() {
    int (&arr_ref)[][3] = A::arr;
    arr_ref[1][2] = 100;
    std::cout << A::arr[1][2] << std::endl;
}

int A::arr[][3] = {{1, 2, 3}, {4, 5, 6}};
