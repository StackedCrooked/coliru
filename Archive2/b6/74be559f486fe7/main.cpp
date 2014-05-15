#include <tuple>
#include <iostream>

template<class A>
void func(A a) {
    std::cout << "First of last: " << std::get<0>(a) << '\n';
}

template<class A, class... Types>
void func(A a, Types... args) {
    std::cout << "First of element: " << std::get<0>(a) << '\n';
    func(args...);
}

int main() {
    func(std::make_tuple(1,2), std::make_tuple("hello"), 42);
}