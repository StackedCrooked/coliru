#include <utility>
#include <tuple>
#include <iostream>

struct A{
    A() {std::cout << "def-ctor\n";}
    A(const A&) {std::cout << "copy-ctor\n";}
    A(A&&) {std::cout << "move-ctor\n";}
    A&operator=(const A&) {std::cout << "copy-asgn\n"; return *this;}
    A&operator=(A&&) {std::cout << "move-asgn\n"; return *this;}
    ~A() {std::cout << "dtor\n";}
};

std::tuple<A, A> func() {
    std::cout << "starting func\n";
    std::tuple<A, A> ret;
    std::cout << "returning from func\n";
    return ret;
}

int main() {
    A one, two;
    std::cout << "entering func\n";
    std::tie(one, two) = func();
    std::cout << "test complete\n";
}