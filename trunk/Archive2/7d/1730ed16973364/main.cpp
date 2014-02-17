#include <atomic>
#include <iostream>

struct foo {
    foo() noexcept {
        std::cout << "foo()\n";
    }
};

int main() {
    std::atomic<foo> bar;
}
