#include <iostream>
#include <utility>

template<typename T>
constexpr auto is_complete(int=0) -> decltype(sizeof(T), bool{}) {
    return true;   
}

template<typename T>
constexpr auto is_complete(...) {return false;}

struct S;

auto xyz() {return is_complete<S>(0);}

struct S{};

int main() {
    std::cout << is_complete<int>(0) << '\n';
    std::cout << xyz() << '\n';
    std::cout << is_complete<S>(0);
}