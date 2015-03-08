auto voldemort = [](int x) {
    struct anon {
        int test;
        anon(int y): test(y) {}
    };
    
    return anon(x);
};

#include <iostream>

int main() {
    auto f = voldemort(10);
    std::cout << f.test << '\n';
}