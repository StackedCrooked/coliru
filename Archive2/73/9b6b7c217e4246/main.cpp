#include <iostream>
#include <string>

void do_foo(int, double, std::initializer_list<std::string> init) {
    std::cout << "Receiving " << init.size() << " strings\n";
}

template <typename... Args>
void foo(int a, double b, Args&&... args) {
    do_foo(a, b, { std::forward<Args>(args)... });
}

int main() { 
    foo(2,  3.14,  "wait a second", "what's the deal here", std::string("quese!"));
    foo(52, 53.14);
}
