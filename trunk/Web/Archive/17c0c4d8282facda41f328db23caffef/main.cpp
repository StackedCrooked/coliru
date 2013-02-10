#include <sstream>
#include <iostream>

char* intToCharPtr(int n) {
    std::stringstream ss;
    ss << n;
    return &(ss.str())[0];
}

void doalmostnothing() {
    int *tmp = new int[500]; std::fill_n(tmp,500,0); delete[] tmp;
}

int main() {
    char* str = intToCharPtr(12345);
    doalmostnothing();
    std::cout << str;
}