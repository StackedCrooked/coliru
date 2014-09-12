#include <iostream>
#include <utility>

template<typename T>
auto is_complete(int) -> decltype(sizeof(std::declval<T>()), bool{}) {
    return true;   
}

template<typename T>
auto is_complete(...) -> bool {
    return false;   
}

struct S;

int main() {
    std::cout << is_complete<int>(0) << '\n';
    std::cout << is_complete<S>(0);
}