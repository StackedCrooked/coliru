#include <iostream>
#include <type_traits>

template<typename T, typename R, typename... Args>
auto call_member_fn(T object, R(T::*func)(Args...), Args && ... args) {
    return ((object).*(func))(std::forward<Args>(args)...);
}

struct A {
    int arf(int a, int b) {
        return a + b;
    }
};

int main() {
    A a;
    std::cout << call_member_fn(a, &A::arf, 1, 2);
}