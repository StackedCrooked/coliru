#include <iostream>
#include <functional>

struct Bool { bool value; };
struct Int { int value; };

static void foo(const std::function<void(Bool)>& f) {
    std::cerr << "using bool overload" << std::endl;
    f(Bool{});
}

static void foo(const std::function<void(Int)>& f) {
    std::cerr << "using int overload" << std::endl;
    f(Int{});
}

int main() {
    foo([](const Bool value) {
        std::cout << std::boolalpha << value.value << std::endl;
    });
    foo([](const Int value) {
        std::cout << value.value << std::endl;
    });
    return 0;
}