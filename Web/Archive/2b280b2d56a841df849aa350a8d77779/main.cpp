#include <sstream>
#include <iostream>

char* intToCharPtr(int n) {
    std::stringstream ss;
    ss << n;
    return &(ss.str())[0];
}

void doalmostnothing() {
    std::stringstream ss; ss << 54321; ss.str();
}

int main() {
    char* str = intToCharPtr(12345);
    doalmostnothing();
    std::cout << str;
}