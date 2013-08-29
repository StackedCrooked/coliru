#include <sstream>
#include <iostream>

char* intToCharPtr(int n) {
    std::stringstream ss;
    ss << n;
    return &(ss.str())[0];
}

int main() {
    char* str = intToCharPtr(12345);
    std::cout << str;
}