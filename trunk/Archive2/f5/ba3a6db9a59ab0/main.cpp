#include <iostream>

void foo() {}
void bar() noexcept {}

int main(){
    std::cout << std::boolalpha << noexcept(foo()) << ' ' << noexcept(bar()) << std::endl;    
}