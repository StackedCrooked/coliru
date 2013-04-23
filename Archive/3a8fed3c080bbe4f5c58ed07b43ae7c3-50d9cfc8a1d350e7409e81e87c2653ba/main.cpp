// Very dumb template examples
#include <iostream>
#include <utility>

template<typename T>
auto sum(T&& a, T&& b) -> decltype(std::forward<T>(a)+std::forward<T>(b)) {
    return std::forward<T>(a)+std::forward<T>(b);
}

class A {
public:
    size_t num;
    explicit A(size_t n): num(n) {}
    auto operator+(A&& a) -> decltype(*this) {
        num += a.num;
        return *this;
    }
    friend auto operator<<(std::ostream& out, const A& a) -> decltype(out) {
        out << a.num;
        return out;
    }
};

int main() {
    std::cout << sum(10,45) << '\n' << sum(1.32334f,1.12412f) << '\n';
    std::cout << sum(A(5),A(10));
}