struct test {
    int x;
    int& y = x;
    
    test(int x): x(x) {}
};

#include <iostream>

int main() {
    test t = { 20 };
    std::cout << t.y << '\n';
}