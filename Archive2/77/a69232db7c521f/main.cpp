#define f(str, ...) str.c_str()

#include <string>
#include <iostream>

int main() {
    std::string str = "hello";
    std::cout << f(str) << '\n';
}