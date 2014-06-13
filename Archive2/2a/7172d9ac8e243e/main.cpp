#include <iostream>

template<typename T>
struct foo {
    foo() {std::cout << "general\n";}
};

template<typename Res, typename Arg>
struct foo<Res(Arg)> {
    foo() {std::cout << "special\n";  }
};

int main() {
    foo<int>();
    foo<int(int)>();
}
