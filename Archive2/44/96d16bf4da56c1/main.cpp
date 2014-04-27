#include <iostream>
enum A { a = (char)1, b, c };   //  underlying type is not fixed

int main() {
    std::cout << sizeof(a) << ' ' << sizeof(A) << '\n';
}