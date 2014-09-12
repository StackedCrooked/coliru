template<typename T>
constexpr auto is_complete_impl(int=0) -> decltype(!sizeof(T)) {
    return true;   
}

template<typename T>
constexpr bool is_complete_impl(...) {return false;}

template<typename T>
constexpr bool is_complete() {
    return is_complete_impl<T>(0);   
}

struct S;

bool xyz() {return is_complete<S>();}

struct S{};

#include <iostream>
int main() {
    std::cout << is_complete<int>() << '\n';
    std::cout << xyz() << '\n';
    std::cout << is_complete<S>();
}