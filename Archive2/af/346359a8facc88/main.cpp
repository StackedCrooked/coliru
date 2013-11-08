#include <iostream>
#include <vector>

struct T {
    T() { std::cout << __PRETTY_FUNCTION__ << std::endl; }
    T(const T&) { std::cout << __PRETTY_FUNCTION__ << std::endl; }
    T(T&&) { std::cout << __PRETTY_FUNCTION__ << std::endl; }
    ~T() { std::cout << __PRETTY_FUNCTION__ << std::endl; }
    T& operator=(const T&) {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        return *this;
    }
    T& operator=(T&&) {
        std::cout << __PRETTY_FUNCTION__ << std::endl;
        return *this;
    }

    void func();
};

T foo() {
    std::cout << __PRETTY_FUNCTION__ << std::endl; // work before declaring return value
    T obj;
    obj.func(); // manipluate object
    return obj;
}

int main() {
    T t = foo();
}

void T::func(){ std::cout << __PRETTY_FUNCTION__ << std::endl; } // not inline