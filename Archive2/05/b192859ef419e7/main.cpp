#include <iostream>

void foo() {}
void bar() noexcept {}
void baz() noexcept(false) {}

int main(){
    std::cout << std::boolalpha << noexcept(foo()) << ' ' << noexcept(bar()) << ' ' << noexcept(baz()) << std::endl;    
}