#include <type_traits>
#include <string>
#include <iostream>

struct A {
    A(const A&) {std::cout << "cctr\n";}
    A(A&&) {std::cout << "mctr\n";}
    A&operator=(const A&) {std::cout << "casn\n"; return*this;}
    A&operator=(A&&) {std::cout << "masn\n"; return*this;}
};

template <typename T>
constexpr typename std::enable_if<
    !std::is_const<
        typename std::remove_reference<T>::type>::value,
    typename std::remove_reference<T>::type&&
>::type
strict_move(T&& x)
{
    return std::move(x);
}

int main() {
    const std::string src = "HI";
    std::string dest = strict_move(src);
}
