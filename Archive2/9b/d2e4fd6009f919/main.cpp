#include <iostream>

struct S {
    explicit S(int) {std::cout << "S(int)\n";}
    S &operator=(int) {std::cout << "operator=(int)\n"; return *this;}
};

int main() {
    S s = 2;   
}