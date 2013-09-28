#include <iostream>
#include <string>
#include <vector>

void one(int a) {
    a = 900;
    std::cout << a << std::endl;   
}

void two(int &a) {
    a = 900;
    std::cout << a << std::endl;   
}

int main() {
    int a = 123;
    one(a);
    std::cout << "after one, a is now: " << a << std::endl;
    two(a);
    std::cout << "after two, a is now: " << a << std::endl;
}
