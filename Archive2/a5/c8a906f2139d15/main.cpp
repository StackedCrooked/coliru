#include <iostream>
#include <string>
#include <vector>
#include <type_traits>
#include <cstring>

struct A {
    int x, y;
};

union {
    long asdf;
    int A::* foo;
} hack;

int main() {
    std::nullptr_t meh{};
    std::memset(&meh, sizeof(meh), 1);
    std::cout << (meh == nullptr) << '\n';
    std::cout << std::is_pod<std::nullptr_t>::value << '\n';
    
    hack.foo = nullptr;
    std::cout << hack.asdf << '\n';
    hack.foo = 0;
    std::cout << hack.asdf << '\n';
}
