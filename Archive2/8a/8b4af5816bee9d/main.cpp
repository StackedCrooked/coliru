#include <iostream>

void foo() {
    std::cout << "foo" << std::endl;
}

template<typename ...Args>
void bar(Args&&... args) {
    auto lambda = [&] () {
        foo(std::forward<Args>(args)...);
    };

    lambda();
}

int main() {
    bar();
}