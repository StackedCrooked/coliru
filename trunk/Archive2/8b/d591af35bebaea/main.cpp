#include <iostream>

template<typename T>
struct Foo {
    Foo();
};

template<>
Foo<int>::Foo() {
    std::cout << "Foo<int>\n";
}

template<>
Foo<void>::Foo() {
    std::cout << "Foo<void>\n";
}

int main()
{
    Foo<int>();
    Foo<void>();
    return 0;
}
