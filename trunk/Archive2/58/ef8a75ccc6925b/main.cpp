#include <iostream>

bool eq(char a, char b) {
    return !(static_cast<int>(a) - static_cast<int>(b));
}

bool are_equal(const char* a, const char* b) {
    int i = 0;
    for (; !eq(a[i], '\0'); ++i)
        if  (!eq(a[i], b[i]))
            return false;
    return (eq(b[i], '\0'));
}

int main(int, char*[]) {
    const char a[] = "Hello";
    const char b[] = "World";
    const char c[] = "Hello";
    std::cout << are_equal(a, b) << '\n';
    std::cout << are_equal(a, c) << '\n';
    std::cout << are_equal(b, c) << '\n';
    std::cout << are_equal(a, a) << '\n';
    std::cout << are_equal(b, b) << '\n';
    std::cout << are_equal(c, c) << '\n';
    return 0;
}