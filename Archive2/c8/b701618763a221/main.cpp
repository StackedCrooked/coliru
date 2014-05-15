#include <iostream>

template<typename T>
struct Foo {
    void bar() {
        std::cout << "bar<T>\n";
    }
};

template<>
void Foo<void>::bar() {
    std::cout << "bar<void>\n";
}

int main()
{
    Foo<int>().bar();
    Foo<void>().bar();
    return 0;
}
