#include<iostream>
#include<string>

void func(int*& ptr) {
    *ptr = 1;
    ptr = 0;
}

int main() {
    int x = 0;
    int* y = &x;
    func(y);
    std::cout << x;
    std::cout << y;
}