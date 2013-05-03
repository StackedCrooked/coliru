#include <iostream>
#include <memory>
#include <typeinfo>

auto make_counter () {
    int i = 0;
    return [=]() mutable { return i++; };
}

std::function<int()> make_counter_f () {
    int i = 0;
    return [=]() mutable { return i++; };
}

int main() {
    auto lambda = make_counter();
    auto func = make_counter_f();
    
    std::cout << typeid( lambda ).name() << std::endl;
    std::cout << typeid( func ).name() << std::endl;
}