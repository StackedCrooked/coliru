#include <iostream>
enum A { a = (char)1, b = sizeof(a), c };   //  underlying type is not fixed

int main() {
    std::cout << sizeof(a) << ' ' << sizeof(A) << ' ' << (int)b << ' ' << '\n';
}