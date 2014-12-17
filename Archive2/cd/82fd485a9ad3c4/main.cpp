#include <iostream>

template<typename... Args>
void bar(Args...) {
    std::cout << sizeof...(Args);
}

template <typename... Args>
void foo(Args&&... args) {
#if TEST == 1
    bar(std::forward<Args>(args...));      // variant 1
#elseif TEST == 2
    bar(std::forward<Args...>(args...));   // variant 2
#else
    bar(std::forward<Args>(args)...);
#endif
}

int main() {
    foo();
    foo(1);
    foo(1,2);
    std::cout << '\n';
}