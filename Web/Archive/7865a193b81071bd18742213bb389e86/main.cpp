#include <functional>
#include <iostream>

void foo(int i = 0) {
    std::cout << i << '\n';    
}

int main() {
    std::function<void(int)> f = foo;
    f();
    f(1);
}