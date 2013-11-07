#include <iostream>

struct base {
    virtual const char* what() const noexcept {
        return "base";
    }
};

struct derived : public base {
    virtual const char* what() const noexcept override {
        return "derived";
    }
};

void a_function(const base& b) {
    std::cout << b.what() << '\n';
}

int main() {
    derived x;
    a_function(x);
}