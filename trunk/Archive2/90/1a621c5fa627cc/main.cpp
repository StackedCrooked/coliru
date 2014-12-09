#include <iostream>

void foo() {}
void bar() noexcept {}
void foo2() noexcept(noexcept(foo())) {}
void bar2() noexcept(noexcept(bar())) {}

int main() {
    std::cout << std::boolalpha << noexcept(foo()) << ' ' << noexcept(bar())
        << ' ' << noexcept(foo2()) << ' ' << noexcept(bar2()) << std::endl;    
}