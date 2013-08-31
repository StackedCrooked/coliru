#include <iostream>
struct Number {
    int n;
    Number(int a):n(a){}

    Number operator++(int i)& {
        ++n;
        return *this;
    }
    Number operator++(int i)&& {
        ++n;
        return std::move(*this);
    }
};

int main() {
    Number x(5);
    x++;
    x++++++++++;
    std::cout << x.n;
}
