#include <type_traits>
#include <string>
#include <iostream>

struct A {
    A(const A&) {std::cout << "cctr\n";}
    A(A&&) {std::cout << "mctr\n";}
    A&operator=(const A&) {std::cout << "casn\n"; return*this;}
    A&operator=(A&&) {std::cout << "masn\n"; return*this;}
};

template<class T>
T&& strict_move(T& x)
{
    static_assert(!std::is_const<T>::value, "parameter is const, would be copied instead of moved");
    return std::move(x);
}

int main() {
    const std::string src = "HI";
    std::string dest = strict_move(src);
}
