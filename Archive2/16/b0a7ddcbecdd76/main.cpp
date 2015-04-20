#include <iostream>

int main() {
    int num = 30;
    int *ptr;
    *ptr = num;

    std::cout << *ptr; // print 30
    std::cout << ptr; // memorry address - 0
}
