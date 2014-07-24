#include <iostream>

struct base {
    virtual ~base() = default;
    
    void one() { std::cout << "one\n"; }
    void two() { std::cout << "two\n"; }
};

struct derived : private base {
    using base::one;
    void three() { std::cout << "three\n"; }
};

int main() {
    derived x;
    x.one();
    x.three();
}