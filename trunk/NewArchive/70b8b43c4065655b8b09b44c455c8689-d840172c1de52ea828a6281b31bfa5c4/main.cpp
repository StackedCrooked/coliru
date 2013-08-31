#include <string>
#include <functional>
#include <iostream>

void f(int a, const std::string& str) {
    std::cout << "a.." << a << "\nstr.." << str << '\n';
}

void f(int a, std::function<void()> f) {
    std::cout << "a.." << a;
    f();
}

template<typename T>
void f(int a, T var = T()) {
    std::cout << "a.." << a << "\nvar..." << var << '\n';
}

int main() {
    f(10,std::string("Hello World!"));
    f(100,10);
    f(1000,[]{std::cout << "lambda?";});
}