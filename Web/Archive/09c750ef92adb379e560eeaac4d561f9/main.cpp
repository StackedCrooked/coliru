int x;

constexpr int blah(int n) {
    return n == 0? 42 : x++;
}

#include <iostream>
int main() {
    blah(0);
    blah(1);
    blah(2);
    std::cout << x;
}