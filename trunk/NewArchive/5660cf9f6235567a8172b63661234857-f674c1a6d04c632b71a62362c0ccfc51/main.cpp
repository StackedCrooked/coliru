#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

template<class tryf_t, class finallyf_t>
void tryf(tryf_t a, finallyf_t b) {
    try {
        a();
        b();
    } catch(...) {
        b();
        throw;
    }
}

int main() {
    tryf([]() {
        std::cout << "test\n";
        throw std::runtime_error("BAAD!");
    }, /* finally */ [] () {
        std::cout << "finally block called\n";
    });
}