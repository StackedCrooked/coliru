#include <type_traits>
#include <iostream>
#include <tuple>

template <int A, int B, int C>
class MyClass {
    friend std::ostream& operator<<(std::ostream& os, const MyClass&) {
        os << '<' << A << ", " << B << ", " << C << '>';
        return os;
    }
};

template <typename T1, typename T2>
struct ChooseFirst;

template <int A1, int B1, int C1, int A2, int B2, int C2>
struct ChooseFirst<MyClass<A1, B1, C1>, MyClass<A2, B2, C2>> {
    static const bool value = std::make_tuple(A1, B1, C1) < std::make_tuple(A2, B2, C2);
};

template <typename T1, typename T2>
typename std::enable_if<ChooseFirst<T1, T2>::value, T1&>::type foo(T1& bar1, T2&) {
    return bar1;
}

template <typename T1, typename T2>
typename std::enable_if<!ChooseFirst<T1, T2>::value, T2&>::type foo(T1&, T2& bar2) {
    return bar2;
}

int main() {
    MyClass<5, 2, 8> m1;
    MyClass<4, 2, 1> m2;
    std::cout << foo(m1, m2) << std::endl;
    std::cout << foo(m2, m1) << std::endl;
}