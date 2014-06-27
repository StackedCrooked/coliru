#include <cstddef>
#include <iostream>

void foo(const char *) {
    std::cout << "foo(const char *)\n";
}

template<std::size_t N>
void foo(const char(&)[N]) {
    std::cout << "foo(const char(&)[N]\n";
}

int main() {
    foo("abc");
    
    char arr[] = "abc";
    foo(arr);
    
    const char arr2[] = "abc";
    foo(arr2);
}