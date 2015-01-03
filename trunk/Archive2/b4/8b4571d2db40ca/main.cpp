#include <functional>
#include <iostream>

void foo(const std::function<int()>& f) {
    std::cout << f() << std::endl;
}

void foo(const std::function<int(int x)>& f) {
std::cout << f(5) << std::endl;
}

int main() {
    foo([](){return 3;});

    foo([](int x){return x;});
}
