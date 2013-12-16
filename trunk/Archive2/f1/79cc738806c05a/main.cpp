#include <iostream>
#include <memory>

struct X {
    X() {
        std::cout << "Construct X" << std::endl;
        std::cout << this << std::endl;
    }
};

static X x;

struct Z {
    Z(const X& x1) : xx(x1) {
        std::cout << "Construct Z" << std::endl;
        std::cout << &x1 << std::endl;
    }
    X xx;
};

struct Y {
    Y(const X& x1) : xx(x1), zz(x1) {
        std::cout << "Construct Y" << std::endl;
        std::cout << &x1 << std::endl;
    }
    X xx;
    Z zz;
};

int main() {
    Y y(x);
    
}