#include <thread>
#include <iostream>

struct foo {
    thread_local static int x;
};
thread_local int foo::x=0;

int main() {
    std::cout << &foo::x;
    std::thread t([] { std::cout << ", " << &foo::x; });
    t.join();
}