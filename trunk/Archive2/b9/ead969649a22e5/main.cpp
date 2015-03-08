#include <iostream>

std::ostream& operator<<(std::ostream& o, const wchar_t* s) {
    while (auto c = *s++) o.put(c);
    return o;
}

int main() {
    std::cout << L"Hello, world";
}