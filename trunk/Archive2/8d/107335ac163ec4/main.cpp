#include <iostream>       
#include <thread>
#include <type_traits>

struct A {
    virtual void foo() { std::cout << "A foo!\n"; }
};

struct B : A {
    void foo() { std::cout << "B foo!\n"; }
};

int main() {
    B b;
    std::thread t{&A::foo, &b};
    t.join();
}