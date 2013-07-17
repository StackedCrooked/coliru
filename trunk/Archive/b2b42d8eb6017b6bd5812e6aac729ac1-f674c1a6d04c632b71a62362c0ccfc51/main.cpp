#include <iostream>

#define FOO(...) #__VA_ARGS__

int main() {
    std::cout << FOO(hello, beautiful,world) << '\n';
}
