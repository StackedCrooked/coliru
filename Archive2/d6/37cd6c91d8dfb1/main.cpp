#include <iostream>

template <class A, class B>
struct Foo {
    static void func() {
        std::cout << "<_, _>\n";
    }
};

/*
template <class B> void Foo<int, B>::func() {
    std::cout << "<int, _>\n";
}

template <class A> void Foo<A, bool>::func() {
    std::cout << "<_, bool>\n";
}
*/

template <> void Foo<char, char>::func() {
    std::cout << "<char, char>\n";
}

int main() {
    Foo<short, short>::func();
    Foo<int, short>::func();
    Foo<short, bool>::func();
    Foo<char, char>::func();
}