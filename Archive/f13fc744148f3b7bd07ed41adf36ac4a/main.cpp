#include <functional>
#include <iostream>

void foo(int i = 0) {
    std::cout << i << '\n';    
}

int main() {
    typedef void (*Function)(int);
    Function f = foo;
    f();
    f(1);
}