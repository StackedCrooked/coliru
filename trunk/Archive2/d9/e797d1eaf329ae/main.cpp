#include <iostream>

struct base {
    virtual const char* what() const noexcept {
        return "base";
    }
};

extern void f();

int main() {
    try {
        f();
    }
    catch(const base& b) {
        std::cerr << b.what() << '\n';
    }
}