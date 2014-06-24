#include <string>
#include <cstdio>
#include <iostream>

std::string foo(const float f) { 
    char buf[6]; 
    sprintf(buf, "%.3f", f); 
    return buf; 
}

int main() {
    std::cout << foo(58896734.5);
}
