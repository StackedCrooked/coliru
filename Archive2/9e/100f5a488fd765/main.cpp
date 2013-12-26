#include <iostream>
#include <algorithm>
#include <string>

int main() {
    char x[] = "Hello";
    std::string y(x);
    std::reverse(std::begin(y), std::end(y));
    std::cout << y;
    return 0;
}