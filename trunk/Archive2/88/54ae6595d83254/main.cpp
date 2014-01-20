#include <iostream>
#include <cassert>

std::nullptr_t operator""_ptr(int i) {
    assert(i == 0);
    return nullptr;
}

int main() {
    char* x = 0_ptr;
    return 0;
}