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

int main() {
    try {
        throw derived();
    }
    catch(const base& b) {
        std::cerr << b.what() << '\n';
    }
}