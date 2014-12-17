#include <iostream>

template<typename... Args>
void bar(Args...) {
    std::cout << sizeof...(Args) << '\n';
}

template <typename... Args>
void foo(Args&&... args) {
    //bar(std::forward<Args>(args...));      // variant 1
    //bar(std::forward<Args...>(args...));   // variant 2
    bar(std::forward<Args>(args)...);
}

int main() {
    foo();
    foo(1);
    foo(1,2);
}