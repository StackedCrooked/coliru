#include <tuple>
#include <iostream>

template<class... Types>
void func(Types...) {
    std::cout << "End";
}

template<class A, class... Types>
void func(A a, Types... args) {
    std::cout << std::get<0>(a);
    func(args...);
}

int main() {
    func(std::make_tuple(1,2), std::make_tuple("hello"), 2);
}