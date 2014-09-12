template<typename T>
constexpr auto is_complete(int=0) -> decltype(!sizeof(T)) {
    return true;   
}

template<typename T>
constexpr bool is_complete(...) {return false;}

struct S;

bool xyz() {return is_complete<S>(0);}

struct S{};

#include <iostream>
int main() {
    std::cout << is_complete<int>(0) << '\n';
    std::cout << xyz() << '\n';
    std::cout << is_complete<S>(0);
}