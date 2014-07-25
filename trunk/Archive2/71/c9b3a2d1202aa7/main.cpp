#include<iostream>

int main () {
    char16_t x[] = { 'a', 'b', 'c', 0 };
    std::cout << sizeof(x[0]) << std::endl;
}