#include <iostream>

class A {
public:
    static int arr[][3];
};

void func(int (&arr_ref)[][3]) {
    std::cout << arr_ref[1][2] << std::endl;
}

int main() {
    int (&arr_ref)[][3] = A::arr;
    
    std::cout << A::arr[1][2] << std::endl;
    
    arr_ref[1][2] = 100;
    std::cout << A::arr[1][2] << std::endl;
    
    arr_ref[1][2] = 200;
    func(arr_ref);
}

int A::arr[][3] = {{1, 2, 3}, {4, 5, 6}};
