#include <iostream>
struct test {
    test() { std::cout << "construct\n"; }
    test(const test&) { std::cout << "copy\n"; }
};

#include <type_traits>

int main() {
    test x;
    test y = test{}; // "copy" isn't printed
    static_assert(std::is_move_constructible<test>::value, "...");
}