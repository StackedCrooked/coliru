#include <sstream>
#include <iostream>

int main() {
    std::stringstream ss = "HELLO";
    char c;
    while(c=ss.get(), ss) {
        std::cout << c;
    }
}